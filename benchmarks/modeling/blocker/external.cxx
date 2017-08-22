
#include "external.hxx"
#include <constraints/registry.hxx>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <tuple>
#include <lapkt/tools/logging.hxx>

External::External( const ProblemInfo& info, const std::string& data_dir ) :
	_nowhere(info.getObjectId("nowhere")),
	_nodes(info.getTypeObjects("node"))
{
    unsigned blocked_pred_sym_id = info.getSymbolId( "blocked" );

    for ( const auto node : _nodes) {
        _blocked_vars[node] = info.resolveStateVariable( blocked_pred_sym_id, {node} );
        _blocked[node] = true;
        _distance_to_exit[node] = _nodes.size();
    }

    _edge_pred_sym = info.getSymbolId( "edge");
    // Determine adjacency list by querying the corresponding extension
    auto edge_pred = info.get_extension(_edge_pred_sym).get_function();
    for ( int i = 0; i < (int)_nodes.size(); i++ )
        for ( int j = 0; j < (int)_nodes.size(); j++ ) {
            if ( !edge_pred( {_nodes[i], _nodes[j]} ) ) continue;
            _edges.push_back( Edge(i,j));
        }

    unsigned exit_pred_sym_id = info.getSymbolId( "exit");
    auto exit_pred = info.get_extension(exit_pred_sym_id).get_function();
    for ( unsigned i = 0; i < _nodes.size(); i++ )
        if ( exit_pred({_nodes[i]}) ) {
            _exit_nodes.push_back(_nodes[i]);
            _exit_nodes_idx.push_back( i );
            _is_exit[_nodes[i]] = true;
        } else {
            _is_exit[_nodes[i]] = false;
        }

    unsigned cat_sym = info.getSymbolId( "cat" );
    _cat_var = info.resolveStateVariable( cat_sym, {} );
    _distance_to_exit.at(_nowhere) = _nodes.size()*_nodes.size();
}

External::~External() {}

void
External::update_graph( const State& s ) const {
    /* Determine blocked nodes */
    LPT_DEBUG( "blocker", "Checking blocked nodes...");
    bool topology_changed = false;
    for ( ObjectIdx o : _nodes ) {
        bool current_value = (s.getValue(_blocked_vars.at(o)) == 1);
        if (current_value != _blocked.at(o)) {
            topology_changed = true;
            _blocked.at(o) = current_value;
        }
        #ifdef DEBUG
        std::string obj_name =  ProblemInfo::getInstance().deduceObjectName(o, ProblemInfo::getInstance().getTypeId("node"));
        std::string status = _blocked.at(o) ? " blocked" : " not blocked";
        #endif
        LPT_DEBUG( "blocker", "\t" << obj_name << " status: " << status );
    }

    if (!topology_changed) {
        LPT_DEBUG("blocker", "Graph topology didn't change");
        return; // Nothing to do here
    }

    /* Graph constructon */
    _maze = Graph(_nodes.size());

    int i, j;

    for ( auto e : _edges ) {
        std::tie( i, j ) = e;
        ObjectIdx nj = _nodes[j];
        if ( /*_blocked[ni] ||*/ _blocked[nj]) continue; // no edge if either end is blocked
        boost::add_edge( i, j, 1, _maze );
        #ifdef DEBUG
        ObjectIdx ni = _nodes[i];

        std::string oi =  ProblemInfo::getInstance().deduceObjectName(ni, ProblemInfo::getInstance().getTypeId("node"));
        std::string oj =  ProblemInfo::getInstance().deduceObjectName(nj, ProblemInfo::getInstance().getTypeId("node"));
        #endif
        LPT_DEBUG("blocker", "Adding edge " << oi << " -> " << oj );
    }
    LPT_DEBUG( "blocker", "Maze graph has " << boost::num_edges(_maze) << " edges");

    //! time to compute the distances to the exit for each of the nodes
    // TODO - MIQUEL: REVISE
    std::vector< int > distances(boost::num_vertices(_maze));
    typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = boost::vertices(_maze); vp.first != vp.second; ++vp.first) {
        auto v = *vp.first;
        #ifdef DEBUG
        std::string obj_name =  ProblemInfo::getInstance().deduceObjectName(_nodes[v], ProblemInfo::getInstance().getTypeId("node"));
        #endif
        LPT_DEBUG( "blocker", "Processing node: " << obj_name );
        if ( _is_exit.at(_nodes[v]) ) {
            LPT_DEBUG( "blocker", "\t is exit: " << obj_name );
            _distance_to_exit.at(_nodes[v]) = 0;
            continue;
        }


        unsigned min_dist = _nodes.size()*_nodes.size();
        boost::dijkstra_shortest_paths( _maze, v, boost::distance_map(distances.data()) );
        for ( auto e : _exit_nodes_idx ) {
            #ifdef DEBUG
            std::string exit_name =  ProblemInfo::getInstance().deduceObjectName(_nodes[e], ProblemInfo::getInstance().getTypeId("node"));
            #endif
            LPT_DEBUG( "blocker", "\t\tdistance to exit node " << exit_name << " is " << distances[e] );
            min_dist = std::min(min_dist, (unsigned)distances[e]);
        }
        LPT_DEBUG( "blocker", "\t min distance to exit: " << min_dist );
        _distance_to_exit.at(_nodes[v]) = min_dist;
    }
}


ObjectIdx
External::cat_moves(const std::vector<ObjectIdx>& arguments ) const {
	throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

bool
External::trapped( const std::vector<ObjectIdx>& arguments ) const {
	throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

ObjectIdx
External::cat_moves(const State& state, const std::vector<ObjectIdx>& arguments ) const {
	assert(arguments.size()==1);

    update_graph(state);
    LPT_DEBUG("blocker", "Graph Updated");
    ObjectIdx src = arguments[0];
    ObjectIdx dest = _nowhere;
    unsigned min_dist = _nodes.size()*_nodes.size();
    typename boost::graph_traits<Graph>::adjacency_iterator ai;
    typename boost::graph_traits<Graph>::adjacency_iterator ai_end;
    for (std::tie(ai, ai_end) = boost::adjacent_vertices(std::find(_nodes.begin(), _nodes.end(),src)-_nodes.begin(), _maze);
            ai != ai_end; ai++ ) {
        if ( _blocked[_nodes[*ai]] ) continue; // destination blocked
        if ( _distance_to_exit.at(_nodes[*ai]) >= min_dist ) continue;
        dest = _nodes[*ai];
        min_dist = _distance_to_exit.at(dest);
    }
    return dest;
}

bool
External::trapped( const State& state, const std::vector<ObjectIdx>& args ) const {
	assert(args.size()==1);

    const ObjectIdxVector& type_objects = ProblemInfo::getInstance().getTypeObjects("node");
    if ( std::find( type_objects.begin(), type_objects.end(), args[0]) == type_objects.end() ) {
        std::string arg0_name =  ProblemInfo::getInstance().deduceObjectName(args[0], ProblemInfo::getInstance().getTypeId("node"));
        throw std::runtime_error("Blocker domain: trapped(s,args): object " + arg0_name + " is not of type 'node'");
    }
    //! Update the graph
    update_graph(state);
    LPT_DEBUG("blocker", "Graph updated...");
    //! The cat is trapped if an exit node is not reachable (i.e. min_{w, w \in exit} d(v,w) = |V|)
    #ifdef DEBUG
    std::string arg0_name =  ProblemInfo::getInstance().deduceObjectName(args[0], ProblemInfo::getInstance().getTypeId("node"));
    #endif
    LPT_DEBUG("blocker", "External::trapped(): arg0=" << arg0_name << " distance_to-exit(arg0)= " <<_distance_to_exit.at(args[0]) );
    return _distance_to_exit.at(args[0]) ==  _nodes.size()*_nodes.size();
}


ObjectIdx
External::distance_to_exit( const State& s, const std::vector<ObjectIdx>& arguments ) const {
    update_graph(s);
    LPT_DEBUG("blocker", "Graph Updated");
    ObjectIdx src = s.getValue(_cat_var);
    ObjectIdx dest = _nowhere;
    unsigned min_dist = _nodes.size()*_nodes.size();
    typename boost::graph_traits<Graph>::adjacency_iterator ai;
    typename boost::graph_traits<Graph>::adjacency_iterator ai_end;
    for (std::tie(ai, ai_end) = boost::adjacent_vertices(std::find(_nodes.begin(), _nodes.end(),src)-_nodes.begin(), _maze);
            ai != ai_end; ai++ ) {
        if ( _blocked[_nodes[*ai]] ) continue; // destination blocked
        if ( _distance_to_exit.at(_nodes[*ai]) >= min_dist ) continue;
        dest = _nodes[*ai];
        min_dist = _distance_to_exit.at(dest);
    }
    LPT_DEBUG("blocker", "Distance to exit: " << min_dist );
    return min_dist;
}

ObjectIdx
External::distance_to_exit( const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

bool
External::prefer( const State& s,  const std::vector<ObjectIdx>& arguments ) const {
	ObjectIdx lhs = arguments[0];
    ObjectIdx rhs = arguments[1];
    update_graph(s);
    // MRJ: Note the tie-breaking
    return _blocked.at(rhs)
            || _distance_to_exit.at(lhs) < _distance_to_exit.at(rhs)
            || ( (_distance_to_exit.at(lhs) == _distance_to_exit.at(rhs))  && (lhs < rhs) );
}

bool
External::closer_or_equal_to_exit( const State& s, const std::vector<ObjectIdx>& args ) const {
    return _distance_to_exit.at(args[0]) <= _distance_to_exit.at(args[1]);
}

bool
External::closer_to_exit( const State& s, const std::vector<ObjectIdx>& args ) const {
    return _distance_to_exit.at(args[0]) < _distance_to_exit.at(args[1]);
}

bool
External::can_block( const std::vector<ObjectIdx>& args ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

bool
External::can_block( const State& s, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx n = args[0];
    if ( n == _nowhere ) return false;
    if ( s.getValue(_blocked_vars.at(n)) ) return false;
    // Determine adjacency list by querying the corresponding extension
    auto edge_pred = ProblemInfo::getInstance().get_extension(_edge_pred_sym).get_function();

    return edge_pred({n, s.getValue(_cat_var)});
}


void External::registerComponents() const {
    LogicalComponentRegistry::instance().
		addFormulaCreator("@trapped", [](const std::vector<const fs::Term*>& subterms){ return new TrappedFormula(subterms); });
    LogicalComponentRegistry::instance().
		addFormulaCreator("@can_block", [](const std::vector<const fs::Term*>& subterms){ return new CanBlockFormula(subterms); });
    LogicalComponentRegistry::instance().
        addTermCreator( "@cat_moves", [](const std::vector<const fs::Term*>& subterms){ return new CatMovesTerm(subterms); });
    LogicalComponentRegistry::instance().
        addTermCreator( "@distance_to_exit", [](const std::vector<const fs::Term*>& subterms){ return new DistanceToExitTerm(subterms); });
}

TrappedFormula::TrappedFormula( const std::vector<const fs::Term*>& subterms)
    : AxiomaticFormula(subterms),
    _external(dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert(subterms.size() == 1);
}

TrappedFormula*
TrappedFormula::clone(const std::vector<const fs::Term*>& subterms) const {
    return new TrappedFormula(subterms);
}

bool
TrappedFormula::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("blocker", "Invoked TrappedFormula::compute()");
    return _external.trapped( state, arguments );
}

CanBlockFormula::CanBlockFormula( const std::vector<const fs::Term*>& subterms)
    : AxiomaticFormula(subterms),
    _external(dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert(subterms.size() == 1);
}

CanBlockFormula*
CanBlockFormula::clone(const std::vector<const fs::Term*>& subterms) const {
    return new CanBlockFormula(subterms);
}

bool
CanBlockFormula::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("blocker", "Invoked CanBlockFormula::compute()");
    return _external.can_block( state, arguments );
}



CatMovesTerm::CatMovesTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@cat_moves" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 1);
}

CatMovesTerm*
CatMovesTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new CatMovesTerm( subterms );
}

ObjectIdx
CatMovesTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("blocker", "Invoked CatMovesTerm::compute()");
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
    LPT_DEBUG("blocker", "Invoked DistanceToExit::compute()");
    return _external.distance_to_exit( state, arguments );
}
