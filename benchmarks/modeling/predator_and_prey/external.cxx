#include "external.hxx"
#include <constraints/registry.hxx>
#include <tuple>
#include <lapkt/tools/logging.hxx>

External::External( const ProblemInfo& info, const std::string& data_dir ) :
    _positions(info.getTypeObjects("position")),
    _predators(info.getTypeObjects("predator")),
    _preys(info.getTypeObjects("prey"))
{
    //! Bind constants
    unsigned max_x_func_sym_id = info.getSymbolId( "max_x" );
    unsigned max_y_func_sym_id = info.getSymbolId( "max_y" );
    unsigned min_x_func_sym_id = info.getSymbolId( "min_x" );
    unsigned min_y_func_sym_id = info.getSymbolId( "min_y" );

    auto max_x = info.get_extension(max_x_func_sym_id).get_function();
    auto max_y = info.get_extension(max_y_func_sym_id).get_function();
    auto min_x = info.get_extension(min_x_func_sym_id).get_function();
    auto min_y = info.get_extension(min_y_func_sym_id).get_function();

    _max_x = max_x({});
    _min_x = min_x({});
    _max_y = max_y({});
    _min_y = min_y({});

    //! Bind position objects to coordinates
    unsigned x_func_sym_id = info.getSymbolId( "x" );
    unsigned y_func_sym_id = info.getSymbolId( "y" );
    auto x = info.get_extension(x_func_sym_id).get_function();
    auto y = info.get_extension(y_func_sym_id).get_function();

    for ( auto o : _positions ) {
        _x_position[o] = x( {o} );
        _y_position[o] = y( {o} );
        _xy2position[ std::make_pair(_x_position[o], _y_position[o])] = o;
    }
    unsigned loc_sym_id = info.getSymbolId( "location" );
    //! Initialize dynamic members
    for ( auto o : _predators ) {
        _location_vars[o] = info.resolveStateVariable( loc_sym_id, {o} );
        _x_predator[o] = 0;
        _y_predator[o] = 0;
    }
    for ( auto o : _preys ) {
        _location_vars[o] = info.resolveStateVariable( loc_sym_id, {o} );
        _x_prey[o] = 0;
        _y_prey[o] = 0;
    }
    for ( auto o : _positions ) {
        _distance_to_predator[o] = 0;
    }
}

External::~External() {

}

void External::registerComponents() const {
    LogicalComponentRegistry::instance().
        addTermCreator( "@update", [](const std::vector<const fs::Term*>& subterms){ return new UpdateTerm(subterms); });
    LogicalComponentRegistry::instance().
        addTermCreator( "@next_move", [](const std::vector<const fs::Term*>& subterms){ return new NextMoveTerm(subterms); });
    LogicalComponentRegistry::instance().
		addFormulaCreator("@trapped", [](const std::vector<const fs::Term*>& subterms){ return new TrappedFormula(subterms); });
}

ObjectIdx
External::update(const std::vector<ObjectIdx>& arguments ) const {
	throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}


ObjectIdx
External::next_move(const std::vector<ObjectIdx>& arguments ) const {
	throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

bool
External::trapped(const std::vector<ObjectIdx>& arguments ) const {
	throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

ObjectIdx
External::update(const State& state, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx old_pos = args[0];
    ObjectIdx dx = args[1];
    ObjectIdx dy = args[2];

    //! Coordinates of old position
    ObjectIdx ox = _x_position.at(old_pos);
    ObjectIdx oy = _y_position.at(old_pos);

    //! Translates input vector by (dx,dy) and clips it to lie within the
    //! bounding box
    ObjectIdx nx = std::max( std::min( ox + dx, _max_x), _min_x);
    ObjectIdx ny = std::max( std::min( oy + dy, _max_y), _min_y);

    ObjectIdx next_pos = _xy2position.at(std::make_pair(nx,ny));

    #ifdef DEBUG
    std::string _old_pos =  ProblemInfo::getInstance().deduceObjectName(old_pos, ProblemInfo::getInstance().getTypeId("position"));
    std::string _dx =  ProblemInfo::getInstance().deduceObjectName(dx, ProblemInfo::getInstance().getTypeId("coord"));
    std::string _dy =  ProblemInfo::getInstance().deduceObjectName(dy, ProblemInfo::getInstance().getTypeId("coord"));
    std::string _nx =  ProblemInfo::getInstance().deduceObjectName(nx, ProblemInfo::getInstance().getTypeId("coord"));
    std::string _ny =  ProblemInfo::getInstance().deduceObjectName(ny, ProblemInfo::getInstance().getTypeId("coord"));
    std::string _next_pos =  ProblemInfo::getInstance().deduceObjectName(next_pos, ProblemInfo::getInstance().getTypeId("position"));
    #endif
    LPT_DEBUG("predator_and_prey", "Translating '" << _old_pos << "' by (" << _dx << "," << _dy << ") -> '" << _next_pos << "' (" << _nx << ", " << ny << ") " );
    return next_pos;
}

ObjectIdx
External::next_move(const State& state, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx pos_prey = args[0];

    //! Update predators positions
    for ( auto o : _predators ) {
        ObjectIdx o_pos = state.getValue(_location_vars.at(o));
        _x_predator.at(o) = _x_position.at(o_pos);
        _y_predator.at(o) = _y_position.at(o_pos);
    }

    //! Calculate min distances from each position adjacent to pos prey
    //! to each predator
    std::set<ObjectIdx> candidates;
    candidates.insert( update(state, {pos_prey, 0, 0}));
    candidates.insert( update(state, {pos_prey, 0, 1}));
    candidates.insert( update(state, {pos_prey, 0, -1}));
    candidates.insert( update(state, {pos_prey, 1, 0}));
    candidates.insert( update(state, {pos_prey, -1, 0}));

    LPT_DEBUG("predator_and_prey", "Calculating move for prey...");
    #ifdef DEBUG
    std::string _pos_prey =  ProblemInfo::getInstance().deduceObjectName(pos_prey, ProblemInfo::getInstance().getTypeId("position"));
    #endif
    LPT_DEBUG("predator_and_prey", "Current prey location is: " << _pos_prey );
    LPT_DEBUG("predator_and_prey", "Candidates:");

    unsigned max_value = 0;
    ObjectIdx safest = pos_prey;
    for ( ObjectIdx np : candidates ) {
        #ifdef DEBUG
        std::string _np =  ProblemInfo::getInstance().deduceObjectName(np, ProblemInfo::getInstance().getTypeId("position"));
        #endif
        LPT_DEBUG("predator_and_prey", "\t =>  " << _np );
        unsigned min_dist_to_predator = _max_x - _min_x + _max_y - _min_y;
        for ( ObjectIdx p : _predators )  {
            unsigned v = std::abs(_x_position.at(np) - _x_predator.at(p))
                        + std::abs(_y_position.at(np) - _y_predator.at(p));

            #ifdef DEBUG
            std::string _p =  ProblemInfo::getInstance().deduceObjectName(p, ProblemInfo::getInstance().getTypeId("predator"));
            #endif
            LPT_DEBUG("predator_and_prey", "\t\t <- " << _p << " @ " << v );
            min_dist_to_predator = std::min( min_dist_to_predator, v );
        }
        LPT_DEBUG("predator_and_prey", "\t =>  Score: " <<  min_dist_to_predator );
        if ( min_dist_to_predator > max_value ) {
            LPT_DEBUG("predator_and_prey", "\t =>  Improves on " << max_value << ", " << _np << " selected" );
            max_value = min_dist_to_predator;
            safest = np;
        }
    }
    #ifdef DEBUG
    std::string _safest =  ProblemInfo::getInstance().deduceObjectName(safest, ProblemInfo::getInstance().getTypeId("position"));
    #endif
    LPT_DEBUG("predator_and_prey", "Prey currently at " << _pos_prey << " moves to " << _safest );
    return safest;
}

bool
External::trapped(const State& s, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx pos_prey = args[0];
    ObjectIdx x_prey = _x_position.at(pos_prey);
    ObjectIdx y_prey = _y_position.at(pos_prey);

    //! Check if prey and at least one of the predators are in the same location
    for ( auto o : _predators ) {
        ObjectIdx o_pos = s.getValue(_location_vars.at(o));
        if ( (_x_position.at(o_pos) == x_prey)
             && ( _y_position.at(o_pos) == y_prey) )
            return true;
    }

    return false;
}


ObjectIdx
External::distance(const State& state, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx predator = args[0];
    ObjectIdx pos_predator = state.getValue( predator );
    ObjectIdx x_pred = _x_predator.at(pos_predator);
    ObjectIdx y_pred = _y_predator.at(pos_predator);

    ObjectIdx prey = args[1];
    ObjectIdx pos_prey = state.getValue( prey );
    ObjectIdx x_prey = _x_position.at(pos_prey);
    ObjectIdx y_prey = _y_position.at(pos_prey);

    ObjectIdx dist = std::abs( x_pred - x_prey) + std::abs( y_pred - y_prey );
    #ifdef DEBUG
    std::string _predator =  ProblemInfo::getInstance().deduceObjectName(predator, ProblemInfo::getInstance().getTypeId("predator"));
    std::string _prey =  ProblemInfo::getInstance().deduceObjectName(prey, ProblemInfo::getInstance().getTypeId("prey"));
    #endif
    LPT_DEBUG("predator_and_prey", "Distance between predator " << _predator << " and prey " << _prey << " is: " << dist );
    return dist;

}

ObjectIdx
External::distance(const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

UpdateTerm::UpdateTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@update" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 3);
}

UpdateTerm*
UpdateTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new UpdateTerm( subterms );
}

ObjectIdx
UpdateTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("predator_and_prey", "Invoked UpdateTerm::compute()");
    return _external.update( state, arguments );
}


NextMoveTerm::NextMoveTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@next_move" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 1);
}

NextMoveTerm*
NextMoveTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new NextMoveTerm( subterms );
}

ObjectIdx
NextMoveTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("predator_and_prey", "Invoked NextMoveTerm::compute()");
    return _external.next_move( state, arguments );
}

DistanceTerm::DistanceTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@distance" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 2);
}

DistanceTerm*
DistanceTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new DistanceTerm( subterms );
}

ObjectIdx
DistanceTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("predator_and_prey", "Invoked DistanceTerm::compute()");
    return _external.distance( state, arguments );
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
    LPT_DEBUG("predator_and_prey", "Invoked TrappedFormula::compute()");
    return _external.trapped( state, arguments );
}
