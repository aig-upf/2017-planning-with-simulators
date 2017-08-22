#include "external.hxx"
#include <constraints/registry.hxx>
#include <tuple>
#include <lapkt/tools/logging.hxx>

External::External( const ProblemInfo& info, const std::string& data_dir ) :
    _puck( info.getTypeObjects("puck")),
    _velocities(info.getTypeObjects("velocity")) {

    //! Game objects
    _top = info.getObjectId("top");
    _bottom = info.getObjectId("bottom");
    _right = info.getObjectId("right");
    _left = info.getObjectId("left");
    _paddle = info.getObjectId("r0");
    _paddle_obs = info.getObjectId("r0_obs");

    //! Paddle radius
    auto radius_func_sym = info.getSymbolId("radius");
    auto radius_func = info.get_extension( radius_func_sym ).get_function();
    _paddle_radius = radius_func({_paddle});

    //! Obstacle bounds
    auto bound_func_sym = info.getSymbolId("bound");
    auto bound_func = info.get_extension( bound_func_sym ).get_function();
    _obs_bound[_top] = bound_func({_top});
    _obs_bound[_bottom] = bound_func({_bottom});
    _obs_bound[_right] = bound_func({_right});
    _obs_bound[_left] = bound_func({_left});
    _obs_bound[_paddle_obs] = bound_func({_paddle_obs});

    //! Bind velocity vectors to values
    unsigned vx_func_sym_id = info.getSymbolId( "vx" );
    unsigned vy_func_sym_id = info.getSymbolId( "vy" );
    auto vx = info.get_extension(vx_func_sym_id).get_function();
    auto vy = info.get_extension(vy_func_sym_id).get_function();

    for (auto vel_vec : _velocities ) {
        _vx[vel_vec] = vx( {vel_vec} );
        _vy[vel_vec] = vy( {vel_vec} );
        _vxvy2vector[ std::make_pair(_vx[vel_vec], _vy[vel_vec])] = vel_vec;
    }

    //! Bind variables associated with paddle and puck
    auto center_sym = info.getSymbolId("center");
    _paddle_center_var = info.resolveStateVariable(center_sym, {_paddle});
    auto prev_dy_sym = info.getSymbolId("prev_dy");
    _paddle_prev_dy_var = info.resolveStateVariable(prev_dy_sym, {_paddle});
    auto current_mode_sym = info.getSymbolId("current_mode");
    _current_mode_var = info.resolveStateVariable(current_mode_sym, {});

    auto x_sym = info.getSymbolId("x");
    auto y_sym = info.getSymbolId("y");
    auto v_vec_sym = info.getSymbolId("v_vec");
    auto a_sym = info.getSymbolId("acceleration");

    for ( auto p : _puck ) {
        _x_puck_var[p] = info.resolveStateVariable( x_sym, {p});
        _y_puck_var[p] = info.resolveStateVariable( y_sym, {p});
        _v_puck_var[p] = info.resolveStateVariable( v_vec_sym, {p});
        _a_puck_var[p] = info.resolveStateVariable( a_sym, {p});
    }

    //! Bind variables counting hits on paddle
    auto hits_sym =  info.getSymbolId("hits");
    for ( auto p : _puck )
        _hits_var[p] = info.resolveStateVariable( hits_sym, {_paddle_obs, p});


}

External::~External() {
}

void External::registerComponents() const {
    LogicalComponentRegistry::instance().
        addTermCreator( "@deflect", [](const std::vector<const fs::Term*>& subterms){ return new DeflectTerm(subterms); });
    LogicalComponentRegistry::instance().
        addTermCreator( "@clamp", [](const std::vector<const fs::Term*>& subterms){ return new ClampTerm(subterms); });
    LogicalComponentRegistry::instance().
        addTermCreator( "@accelerate", [](const std::vector<const fs::Term*>& subterms){ return new AccelerateTerm(subterms); });
    LogicalComponentRegistry::instance().
        addTermCreator( "@get_puck_pixel", [](const std::vector<const fs::Term*>& subterms){ return new GetPuckPixelTerm(subterms); });

    LogicalComponentRegistry::instance().
		addFormulaCreator("@collision", [](const std::vector<const fs::Term*>& subterms){ return new CollisionFormula(subterms); });
    LogicalComponentRegistry::instance().
		addFormulaCreator("@not_collision", [](const std::vector<const fs::Term*>& subterms){ return new NotCollisionFormula(subterms); });
    LogicalComponentRegistry::instance().
		addFormulaCreator("@game_on", [](const std::vector<const fs::Term*>& subterms){ return new GameOnFormula(subterms); });

}


ObjectIdx
External::clamp(const State& state, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx x = args[0];
    ObjectIdx lb = args[1];
    ObjectIdx ub = args[2];
    return std::max( lb, std::min( x, ub) );
}

ObjectIdx
External::clamp(const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

ObjectIdx
External::deflect(const State& state, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx obs = args[0];
    ObjectIdx vel_vec = args[1];
    #ifdef DEBUG
    std::string _obs = ProblemInfo::getInstance().deduceObjectName(obs, ProblemInfo::getInstance().getTypeId("obstacle"));
    #endif
    ObjectIdx vx = _vx.at(vel_vec);
    ObjectIdx vy = _vy.at(vel_vec);
    LPT_DEBUG( "pong", "Deflecting object incoming on obstacle '" << _obs << "' with velocity vector (" << vx << "," << vy << ")" );
    if ( obs == _top ) {
        LPT_DEBUG( "pong", "\tTop deflection");
        //! Change sign of vy
        vy = -vy;
        ObjectIdx new_vec =  _vxvy2vector.at( std::make_pair(vx,vy) );
        #ifdef DEBUG
        std::string _new_vec = ProblemInfo::getInstance().deduceObjectName( new_vec, ProblemInfo::getInstance().getTypeId("velocity"));
        #endif
        LPT_DEBUG( "pong", "\t\tvx = " << vx << " vy = " << vy << " vector = " << _new_vec );
        return new_vec;
    }
    if ( obs == _bottom ) {
        LPT_DEBUG( "pong", "\tBottom deflection");
        //! Change sign of vy
        vy = -vy;
        ObjectIdx new_vec =  _vxvy2vector.at( std::make_pair(vx,vy) );
        #ifdef DEBUG
        std::string _new_vec = ProblemInfo::getInstance().deduceObjectName( new_vec, ProblemInfo::getInstance().getTypeId("velocity"));
        #endif
        LPT_DEBUG( "pong", "\t\tvx = " << vx << " vy = " << vy << " vector = " << _new_vec );
        return new_vec;
    }
    if ( obs == _right) {
        LPT_DEBUG( "pong", "\tRight deflection");
        //! Change sign of vx
        vx = -vx;
        ObjectIdx new_vec =  _vxvy2vector.at( std::make_pair(vx,vy) );
        #ifdef DEBUG
        std::string _new_vec = ProblemInfo::getInstance().deduceObjectName( new_vec, ProblemInfo::getInstance().getTypeId("velocity"));
        #endif
        LPT_DEBUG( "pong", "\t\tvx = " << vx << " vy = " << vy << " vector = " << _new_vec );
        return new_vec;
    }
    if ( obs == _left) {
        LPT_DEBUG( "pong", "\tLeft deflection");
        //! Ball gets stuck
        vx = 0;
        vy = 0;
        ObjectIdx new_vec =  _vxvy2vector.at( std::make_pair(vx,vy) );
        #ifdef DEBUG
        std::string _new_vec = ProblemInfo::getInstance().deduceObjectName( new_vec, ProblemInfo::getInstance().getTypeId("velocity"));
        #endif
        LPT_DEBUG( "pong", "\t\tvx = " << vx << " vy = " << vy << " vector = " << _new_vec );
        return new_vec;
    }
    assert( obs == _paddle_obs );
    LPT_DEBUG( "pong", "\tPaddle deflection");
    //! Change sign of vx
    vx = -vx;
    ObjectIdx new_vec =  _vxvy2vector.at( std::make_pair(vx,vy) );
    #ifdef DEBUG
    std::string _new_vec = ProblemInfo::getInstance().deduceObjectName( new_vec, ProblemInfo::getInstance().getTypeId("velocity"));
    #endif
    LPT_DEBUG( "pong", "\t\tvx = " << vx << " vy = " << vy << " vector = " << _new_vec );
    return new_vec;
}

ObjectIdx
External::deflect(const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

ObjectIdx
External::accelerate(const State& state, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx current_accel = args[1];
    ObjectIdx obs = args[0];
    ObjectIdx current_vel = args[2];
    if ( obs != _paddle_obs ) return current_accel;
    LPT_DEBUG( "pong", "Computing paddle acceleration effect");
    ObjectIdx vy = _vy.at(current_vel);
    LPT_DEBUG( "pong", "\tIncoming velocity vector y-component: " << vy << ")" );
    LPT_DEBUG( "pong", "\tCurrent acceleration " << current_accel );
    ObjectIdx prev_dy = state.getValue(_paddle_prev_dy_var);
    if ( vy == prev_dy )
        current_accel = std::max(std::min(current_accel+1,5), 1);
    else
        current_accel = std::max(std::min(current_accel-1,5), 1);
    LPT_DEBUG( "pong", "\tResulting acceleration " << current_accel );

    return current_accel;
}

ObjectIdx
External::accelerate(const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

bool
External::collision(const State& state, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx x = args[0];
    ObjectIdx y = args[1];
    ObjectIdx obs = args[2];
    #ifdef DEBUG
    std::string _obs = ProblemInfo::getInstance().deduceObjectName(obs, ProblemInfo::getInstance().getTypeId("obstacle"));
    #endif
    LPT_DEBUG( "pong", "Collision testing: x(obj)=" << x << ", y(obj)=" << y << ", obstacle=" << _obs);
    if ( obs == _top ) {
        #ifdef DEBUG
        if (y >= _obs_bound.at(_top))
            LPT_DEBUG("pong", "\tPONG!");
        #endif
        return y >= _obs_bound.at(_top);
    }
    if ( obs == _bottom ) {
        #ifdef DEBUG
        if (y == _obs_bound.at(_bottom))
            LPT_DEBUG("pong", "\tPONG!");
        #endif
        return y <= _obs_bound.at(_bottom);
    }
    if ( obs == _right ) {
        #ifdef DEBUG
        if (x >= _obs_bound.at(_right))
            LPT_DEBUG("pong", "\tPONG!");
        #endif
        return x >= _obs_bound.at(_right);
    }
    if ( obs == _left ) {
        #ifdef DEBUG
        if (x <= _obs_bound.at(_left))
            LPT_DEBUG("pong", "\tZONK!");
        #endif
        return x <= _obs_bound.at(_left);
    }

    assert( obs == _paddle_obs );
    if ( x != _obs_bound.at(_paddle_obs) ) return false;
    ObjectIdx cy = state.getValue(_paddle_center_var);
    LPT_DEBUG( "pong", "Paddle extent: [" << cy-_paddle_radius << ", " << cy+_paddle_radius << "]" );
    if ( y < (cy - _paddle_radius) || y > (cy + _paddle_radius) ) return false;
    LPT_DEBUG("pong", "\tPONG!");
    return true;
}

bool
External::collision(const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

bool
External::game_on(const State& s, const std::vector<ObjectIdx>& args ) const {
    LPT_DEBUG("pong", "Checking whether the game is still on...");
    for ( auto p : _puck ) {
        ObjectIdx v_p = s.getValue( _v_puck_var.at(p) );
        #ifdef DEBUG
        std::string _p = ProblemInfo::getInstance().deduceObjectName( p, ProblemInfo::getInstance().getTypeId("puck"));
        #endif
        ObjectIdx vx_p = _vx.at( v_p );
        ObjectIdx vy_p = _vy.at( v_p );
        LPT_DEBUG( "pong", "\tVelocity of puck '" <<  _p << "' is vx=" << vx_p << ", vy=" << vy_p );
        if ( vx_p != 0 && vy_p != 0 ) {
            return true;
        }
    }
    LPT_DEBUG( "pong", "All pucks STUCK!")
    return false;
}


bool
External::game_on(const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}


bool
External::not_collision(const State& state, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx x = args[0];
    ObjectIdx y = args[1];
    ObjectIdx obs = args[2];
    #ifdef DEBUG
    std::string _obs = ProblemInfo::getInstance().deduceObjectName(obs, ProblemInfo::getInstance().getTypeId("obstacle"));
    #endif
    LPT_DEBUG( "pong", "Testing for non-collision: x(obj)=" << x << ", y(obj)=" << y << ", obstacle=" << _obs);
    if ( obs == _top ) {
        #ifdef DEBUG
        if (y < _obs_bound.at(_top))
            LPT_DEBUG("pong", "\t<nothing>");
        #endif
        return y < _obs_bound.at(_top);
    }
    if ( obs == _bottom ) {
        #ifdef DEBUG
        if (y > _obs_bound.at(_bottom))
            LPT_DEBUG("pong", "\t<nothing>!");
        #endif
        return y > _obs_bound.at(_bottom);
    }
    if ( obs == _right ) {
        #ifdef DEBUG
        if (x < _obs_bound.at(_right))
            LPT_DEBUG("pong", "\t<nothing>!");
        #endif
        return x < _obs_bound.at(_right);
    }
    if ( obs == _left ) {
        #ifdef DEBUG
        if (x > _obs_bound.at(_left))
            LPT_DEBUG("pong", "\t<nothing>!");
        #endif
        return x > _obs_bound.at(_left);
    }
    assert( obs == _paddle_obs );
    ObjectIdx cy = state.getValue(_paddle_center_var);
    LPT_DEBUG( "pong", "Paddle extent: [" << cy-_paddle_radius << ", " << cy+_paddle_radius << "]" );
    if ( x !=  _obs_bound.at(_paddle_obs) ) return true;

    if ( y < (cy - _paddle_radius) || y > (cy + _paddle_radius) ) return true;
    LPT_DEBUG("pong", "\t<nothing>!");
    return false;
}

bool
External::not_collision(const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

ObjectIdx
External::sum_hits(const State& state, const std::vector<ObjectIdx>& arguments ) const {
    ObjectIdx sum = 0;

    LPT_DEBUG("pong", "Checking hits...");
    for ( auto p : _puck ) {
        ObjectIdx hits_p = state.getValue(_hits_var.at(p));
        #ifdef DEBUG
        std::string _p = ProblemInfo::getInstance().deduceObjectName(p, ProblemInfo::getInstance().getTypeId("puck"));
        #endif
        LPT_DEBUG( "pong", "\t hits for puck " << _p << " are: " << hits_p );
        sum += hits_p;
    }
    LPT_DEBUG( "pong", "Sum of hits: " << sum );
    return sum;
}

ObjectIdx
External::sum_hits(const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

ObjectIdx
External::distance_to_paddle(const State& state, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx the_puck = args[0];
    #ifdef DEBUG
    std::string _p = ProblemInfo::getInstance().deduceObjectName(the_puck, ProblemInfo::getInstance().getTypeId("puck"));
    #endif
    LPT_DEBUG( "pong", "Computing distance to paddle for puck: " << _p );
    ObjectIdx puck_vel = state.getValue( _v_puck_var.at(the_puck) );
    ObjectIdx vx = _vx.at(puck_vel);
    LPT_DEBUG( "pong", "\tIncoming velocity vector x-component: " << vx  << ")" );
    if ( vx >= 0 ) {
        LPT_DEBUG("pong", "\t Puck is moving away from paddle...");
        return _obs_bound.at(_right);
    }

    ObjectIdx x = state.getValue( _x_puck_var.at(the_puck));
    ObjectIdx y = state.getValue( _y_puck_var.at(the_puck));

    if ( x <= 1 ) {
        LPT_DEBUG("pong", "\t Puck is gone already...");
        return _obs_bound.at(_left);
    }

    ObjectIdx cy = state.getValue(_paddle_center_var);
    ObjectIdx distance = (x - 2) + std::abs(cy - y);
    LPT_DEBUG("pong", "Distance to paddle: " << distance );

    // MRJ: We take the tuple here!
    return distance * state.getValue(_current_mode_var) + state.getValue(_hits_var.at(the_puck));
}

ObjectIdx
External::distance_to_paddle(const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

ObjectIdx
External::get_puck_pixel(const State& state, const std::vector<ObjectIdx>& args ) const {
    ObjectIdx the_puck = args[0];

    ObjectIdx offset = state.getValue(_x_puck_var.at(the_puck)) * _obs_bound.at(_right )
                        + state.getValue(_y_puck_var.at(the_puck)) * _obs_bound.at(_top)
                        + state.getValue(_current_mode_var);
    return offset;
}

ObjectIdx
External::get_puck_pixel(const std::vector<ObjectIdx>& arguments ) const {
    throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

DeflectTerm::DeflectTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@deflect" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 2);
}

DeflectTerm*
DeflectTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new DeflectTerm( subterms );
}

ObjectIdx
DeflectTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pong", "Invoked DeflectTerm::compute()");
    return _external.deflect( state, arguments );
}


ClampTerm::ClampTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@clamp" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 3);
}

ClampTerm*
ClampTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new ClampTerm( subterms );
}

ObjectIdx
ClampTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pong", "Invoked ClampTerm::compute()");
    return _external.clamp( state, arguments );
}

AccelerateTerm::AccelerateTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@accelerate" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 3);
}

AccelerateTerm*
AccelerateTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new AccelerateTerm( subterms );
}

ObjectIdx
AccelerateTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pong", "Invoked AccelerateTerm::compute()");
    return _external.accelerate( state, arguments );
}

CollisionFormula::CollisionFormula( const std::vector<const fs::Term*>& subterms)
    : AxiomaticFormula(subterms),
    _external(dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert(subterms.size() == 3);
}

CollisionFormula*
CollisionFormula::clone(const std::vector<const fs::Term*>& subterms) const {
    return new CollisionFormula(subterms);
}

bool
CollisionFormula::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pong", "Invoked CollisionFormula::compute()");
    return _external.collision( state, arguments );
}


NotCollisionFormula::NotCollisionFormula( const std::vector<const fs::Term*>& subterms)
    : AxiomaticFormula(subterms),
    _external(dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert(subterms.size() == 3);
}

NotCollisionFormula*
NotCollisionFormula::clone(const std::vector<const fs::Term*>& subterms) const {
    return new NotCollisionFormula(subterms);
}

bool
NotCollisionFormula::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pong", "Invoked NotCollisionFormula::compute()");
    return _external.not_collision( state, arguments );
}

GameOnFormula::GameOnFormula( const std::vector<const fs::Term*>& subterms)
    : AxiomaticFormula(subterms),
    _external(dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert(subterms.size() == 0);
}

GameOnFormula*
GameOnFormula::clone(const std::vector<const fs::Term*>& subterms) const {
    return new GameOnFormula(subterms);
}

bool
GameOnFormula::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pong", "Invoked GameOnFormula::compute()");
    return _external.game_on( state, arguments );
}

SumHitsTerm::SumHitsTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@sum_hits" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 0);
}

SumHitsTerm*
SumHitsTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new SumHitsTerm( subterms );
}

ObjectIdx
SumHitsTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pong", "Invoked SumHitsTerm::compute()");
    return _external.sum_hits( state, arguments );
}

DistanceToPaddleTerm::DistanceToPaddleTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@distance_to_paddle" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 1);
}

DistanceToPaddleTerm*
DistanceToPaddleTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new DistanceToPaddleTerm( subterms );
}

ObjectIdx
DistanceToPaddleTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pong", "Invoked DistanceToPaddleTerm::compute()");
    return _external.distance_to_paddle( state, arguments );
}

GetPuckPixelTerm::GetPuckPixelTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@get_puck_pixel" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 1);
}

GetPuckPixelTerm*
GetPuckPixelTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new GetPuckPixelTerm( subterms );
}

ObjectIdx
GetPuckPixelTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pong", "Invoked GetPuckPixelTerm::compute()");
    return _external.get_puck_pixel( state, arguments );
}
