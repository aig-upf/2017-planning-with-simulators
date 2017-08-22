
#include "external.hxx"
#include <constraints/registry.hxx>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <tuple>
#include <lapkt/tools/logging.hxx>

External::External( const ProblemInfo& info, const std::string& data_dir ) :
    _nowhere(info.getObjectId("nowhere")),
	_nodes(info.getTypeObjects("node")),
    _cats(info.getTypeObjects("cat"))
{
    unsigned light_pred_sym_id = info.getSymbolId( "light" );

    for ( const auto node : _nodes) {
        _light_vars[node] = info.resolveStateVariable( light_pred_sym_id, {node} );
        _alight[node] = false;
        _distance_to_light[node] = _nodes.size();
    }
    /* Graph constructon */
    _map = Graph(_nodes.size());

    unsigned edge_pred_sym_id = info.getSymbolId( "edge");
    // Determine adjacency list by querying the corresponding extension
    auto edge_pred = info.get_extension(edge_pred_sym_id).get_function();
    for ( int i = 0; i < (int)_nodes.size(); i++ )
        for ( int j = 0; j < (int)_nodes.size(); j++ ) {
            if ( !edge_pred( {_nodes[i], _nodes[j]} ) ) continue;
            boost::add_edge( i, j, 1, _map );
            #ifdef DEBUG
            std::string oi =  ProblemInfo::getInstance().deduceObjectName(_nodes[i], ProblemInfo::getInstance().getTypeId("node"));
            std::string oj =  ProblemInfo::getInstance().deduceObjectName(_nodes[j], ProblemInfo::getInstance().getTypeId("node"));
            #endif
            LPT_DEBUG("helper", "Adding edge " << oi << " -> " << oj );
        }

    LPT_DEBUG( "helper", "Map graph has " << boost::num_edges(_map) << " edges");

    unsigned exit_pred_sym_id = info.getSymbolId( "exit");
    auto exit_pred = info.get_extension(exit_pred_sym_id).get_function();
    for ( unsigned i = 0; i < _nodes.size(); i++ )
        _is_exit[_nodes[i]] = exit_pred({_nodes[i]});

    unsigned loc_sym = info.getSymbolId("location");
    unsigned view_range_sym = info.getSymbolId("view_range");
    auto view_range_func = info.get_extension(view_range_sym).get_function();
    for ( auto c : _cats ) {
        _cat_location_vars[c] = info.resolveStateVariable( loc_sym, {c} );
        _cat_location[c] = _nowhere;
        _cat_view_ranges[c] = view_range_func({c});
    }
    std::vector< int > distances(boost::num_vertices(_map));
    typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = boost::vertices(_map); vp.first != vp.second; ++vp.first) {
        auto v = *vp.first;
        #ifdef DEBUG
        std::string obj_name =  ProblemInfo::getInstance().deduceObjectName(_nodes[v], ProblemInfo::getInstance().getTypeId("node"));
        #endif
        LPT_DEBUG( "helper", "Processing location: " << obj_name );
        if (_is_exit.at(_nodes[v])) {
            LPT_DEBUG( "helper", "\t Exit, no contribution to sum!");
            _distance_to_exit[_nodes[v] ] = 0;
        }
        unsigned min_dist = _nodes.size();
        boost::dijkstra_shortest_paths( _map, v, boost::distance_map(distances.data()) );
        for ( unsigned i = 0; i < _nodes.size(); i++ ) {
            _distance[std::make_pair(_nodes[v],_nodes[i])] = distances[i];
            if ( !_is_exit.at(_nodes[i])) continue;
            #ifdef DEBUG
            std::string node_name =  ProblemInfo::getInstance().deduceObjectName(_nodes[i], ProblemInfo::getInstance().getTypeId("node"));
            #endif
            LPT_DEBUG( "helper", "\t\tdistance to exit node " << node_name << " is " << distances[i] );
            min_dist = std::min(min_dist, (unsigned)distances[i]);
        }
        LPT_DEBUG( "helper", "\t min distance to exit: " << min_dist );
        _distance_to_exit[_nodes[v]] = 0;
    }

    for ( auto n : _nodes ) {
        _distance[std::make_pair(_nowhere,n)] = _nodes.size() * _nodes.size();
        _distance[std::make_pair(n,_nowhere)] = _nodes.size() * _nodes.size();

    }
}

External::~External() {}

void
External::update_graph( const State& s ) const {
    /* Determine blocked nodes */
    LPT_DEBUG( "helper", "Checking illuminated nodes...");
    bool illumination_changed = false;
    for ( ObjectIdx o : _nodes ) {
        bool current_value = (s.getValue(_light_vars.at(o)) == 1);
        if ( current_value != _alight.at(o) ) {
            illumination_changed = true;
            _alight.at(o) = current_value;
        }
        #ifdef DEBUG
        std::string obj_name =  ProblemInfo::getInstance().deduceObjectName(o, ProblemInfo::getInstance().getTypeId("node"));
        std::string status = _alight.at(o) ? " illuminated" : " dark";
        #endif
        LPT_DEBUG( "helper", "\t" << obj_name << " status: " << status );
    }

    if (!illumination_changed) {
        LPT_DEBUG("helper", "Lighting didn't change");
        return; // Nothing to do here
    }

    //! time to compute the distances to the exit for each of the nodes
    // TODO - MIQUEL: REVISE
    std::vector< int > distances(boost::num_vertices(_map));
    typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = boost::vertices(_map); vp.first != vp.second; ++vp.first) {
        auto v = *vp.first;
        #ifdef DEBUG
        std::string obj_name =  ProblemInfo::getInstance().deduceObjectName(_nodes[v], ProblemInfo::getInstance().getTypeId("node"));
        #endif
        LPT_DEBUG( "helper", "Processing node: " << obj_name );
        if (_alight.at(_nodes[v])) {
            _distance_to_light.at(_nodes[v]) = 0;
            continue;
        }
        unsigned min_dist = _nodes.size();
        boost::dijkstra_shortest_paths( _map, v, boost::distance_map(distances.data()) );
        for ( unsigned i = 0; i < _nodes.size(); i++ ) {
            if ( !_alight.at(_nodes[i])) continue;
            #ifdef DEBUG
            std::string node_name =  ProblemInfo::getInstance().deduceObjectName(_nodes[i], ProblemInfo::getInstance().getTypeId("node"));
            #endif
            LPT_DEBUG( "helper", "\t\tdistance to alight node " << node_name << " is " << distances[i] );
            min_dist = std::min(min_dist, (unsigned)distances[i]);
        }
        LPT_DEBUG( "helper", "\t min distance to light: " << min_dist );
        _distance_to_light.at(_nodes[v]) = min_dist;
    }
}


ObjectIdx
External::cat_moves(const std::vector<ObjectIdx>& arguments ) const {
	throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}


ObjectIdx
External::cat_moves(const State& state, const std::vector<ObjectIdx>& arguments ) const {
	assert(arguments.size()==2);

    update_graph(state);
    LPT_DEBUG("helper", "Graph Updated");
    ObjectIdx src = arguments[1];
    if ( _alight[src]) return src;
    ObjectIdx dest = src;

    unsigned min_dist = _nodes.size();
    typename boost::graph_traits<Graph>::adjacency_iterator ai;
    typename boost::graph_traits<Graph>::adjacency_iterator ai_end;
    for (std::tie(ai, ai_end) = boost::adjacent_vertices(std::find(_nodes.begin(), _nodes.end(),src)-_nodes.begin(), _map);
            ai != ai_end; ai++ ) {
        if ( 1 + _distance_to_light.at(_nodes[*ai]) >= min_dist ) continue;
        // MRJ: actual distance to the light is 1 + min_{w \in lighted} dist(v,w)
        if ( 1 + _distance_to_light.at(_nodes[*ai]) > arguments[0] ) continue;
        dest = _nodes[*ai];
        min_dist = _distance_to_light.at(dest);
    }
    #ifdef DEBUG
    std::string node_name =  ProblemInfo::getInstance().deduceObjectName(dest, ProblemInfo::getInstance().getTypeId("node"));
    #endif
    LPT_DEBUG( "helper", "Cat moves to node: " << node_name << ", distance to light from there is" << min_dist + 1 );
    return dest;
}

ObjectIdx
External::distance_to_exit(const State& state, const std::vector<ObjectIdx>& args ) const {

    //! Update cat locations
    ObjectIdx the_cat = args[0];
    return _distance_to_exit[ state.getValue( _cat_location_vars.at(the_cat))];
}

ObjectIdx
External::distance_to_exit(const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

bool
External::can_view( const std::vector<ObjectIdx>& args ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

bool
External::can_view( const State& s, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx the_cat = args[0];
    ObjectIdx cat_loc = s.getValue( _cat_location_vars.at(the_cat));
    ObjectIdx target = args[1];

    return _distance.at(std::make_pair(cat_loc,target)) <= _cat_view_ranges.at(the_cat);
}

void External::registerComponents() const {
    LogicalComponentRegistry::instance().
        addFormulaCreator("@can_view", [](const std::vector<const fs::Term*>& subterms){ return new CanViewFormula(subterms); });
    LogicalComponentRegistry::instance().
        addTermCreator( "@cat_moves", [](const std::vector<const fs::Term*>& subterms){ return new CatMovesTerm(subterms); });
    LogicalComponentRegistry::instance().
        addTermCreator( "@distance_to_exit", [](const std::vector<const fs::Term*>& subterms){ return new DistanceToExitTerm(subterms); });
}

CanViewFormula::CanViewFormula( const std::vector<const fs::Term*>& subterms)
    : AxiomaticFormula(subterms),
    _external(dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert(subterms.size() == 2);
}

CanViewFormula*
CanViewFormula::clone(const std::vector<const fs::Term*>& subterms) const {
    return new CanViewFormula(subterms);
}

bool
CanViewFormula::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("helper", "Invoked CanViewFormula::compute()");
    return _external.can_view( state, arguments );
}

CatMovesTerm::CatMovesTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@cat_moves" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 2);
}

CatMovesTerm*
CatMovesTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new CatMovesTerm( subterms );
}

ObjectIdx
CatMovesTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("helper", "Invoked CatMovesTerm::compute()");
    return _external.cat_moves( state, arguments );
}

DistanceToExitTerm::DistanceToExitTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@distance_to_exit" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
        assert( subterms.size() == 1);
}

DistanceToExitTerm*
DistanceToExitTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new DistanceToExitTerm( subterms );
}

ObjectIdx
DistanceToExitTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("helper", "Invoked DistanceToExitTerm::compute()");
    return _external.distance_to_exit( state, arguments );
}
