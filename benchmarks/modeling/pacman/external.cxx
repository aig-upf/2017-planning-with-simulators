#include "external.hxx"
#include <constraints/registry.hxx>
#include <tuple>
#include <lapkt/tools/logging.hxx>
#include <boost/filesystem.hpp>
#include <fstream>
#include <sstream>
#include <cmath>

namespace boost_fs = boost::filesystem;

External::External( const ProblemInfo& info, const std::string& data_dir ) :
    _pacman(info.getTypeObjects("pacman")),
    _ghost(info.getTypeObjects("ghost")),
    _location(info.getTypeObjects("location")),
    _width(0)
{

    //! map layout file
    unsigned map_layout_sym_id = info.getSymbolId( "map_layout" );
    auto map_layout = info.get_extension(map_layout_sym_id).get_function();
    std::string map_name = info.deduceObjectName( map_layout({}), "layout") + ".lay";

    boost_fs::path map_file = boost_fs::path(data_dir) / boost_fs::path("layouts") / boost_fs::path(map_name);

    if (!boost_fs::exists(map_file))
        throw std::runtime_error("[Pacman::External]: Could not open map data file '" + map_file.string() + "' for map '" + map_name + "'");
    if (!boost_fs::is_regular_file(map_file))
        throw std::runtime_error("[Pacman::External]: Map data file '" + map_file.string() + "' cannot be opened");

    std::ifstream input(map_file.string());

    if ( !input.is_open() )
        throw std::runtime_error("[Pacman::External]: Failed to open map data file '" + map_file.string() + "'");

    int loc_idx = 1;
    int x = 0;
    int y = 0;
    int ghost = 0;

    for ( std::string line; std::getline(input,line);) {
        if ( _width == 0 ) _width = line.size();
        if ( line.size() != _width ) {
            std::stringstream ss;
            ss << "[Pacman::External]: line width mismatch, got ";
            ss << line.size() << " expected " << _width << std::endl;
            throw std::runtime_error( ss.str() );
        }
        x = 0;
        for ( auto c : line ) {
            if (c == '%') {
                _blocked[ loc_idx ] = true;
            }
            else if (c == 'P') {
                _blocked[ loc_idx ] = false;
            }
            else if (c == '.') {
                _blocked[ loc_idx ] = false;
            }
            else if (c == 'G' ) {
                _blocked[ loc_idx ] = false;
				++ghost;
            } else if (c == ' ' ) {
				_blocked[ loc_idx ] = false;
				
			} 
            else if (c == 'o' ) {  // At the moment we just ignore  capsules
				_blocked[ loc_idx ] = false;
				
			} 			
			else {
				LPT_INFO("cout", "Unknown PACMAN encoding char: " << c);
				throw std::runtime_error("Unknown PACMAN encoding char!!!");
			}
				
				
            _location_x[ loc_idx ] = x;
            _location_y[ loc_idx ] = y;
            LPT_DEBUG("pacman", "Initialised: loc idx #" << loc_idx << " object = " << loc_idx );
            LPT_DEBUG("pacman", "\t blocked? " << _blocked[ loc_idx ]);
            LPT_DEBUG("pacman", "\t x? " << _location_x[ loc_idx ]);
            LPT_DEBUG("pacman", "\t y? " << _location_y[ loc_idx ]);

            x++;
            loc_idx++;
        }
        y++;
    }
    LPT_DEBUG("pacman", "Loaded map: '" << map_file << "'" );
    LPT_DEBUG("pacman", "\t # Locations: " << loc_idx << " width: " << _width << " height: " << y );
}

External::~External() {

}

void External::registerComponents() const {
    LPT_DEBUG("pacman", "Registering Components...");
    LogicalComponentRegistry::instance().
        addTermCreator( "@move_ghost", [](const std::vector<const fs::Term*>& subterms){ return new MoveGhostTerm(subterms); });
    LogicalComponentRegistry::instance().
		addFormulaCreator("@valid_move", [](const std::vector<const fs::Term*>& subterms){ return new ValidMoveFormula(subterms); });
}


ObjectIdx
External::move_ghost(const std::vector<ObjectIdx>& args ) const {
    assert( args.size() == 2 );
    ObjectIdx ghost_loc = args[0];
	ObjectIdx pacman_loc = args[1];

	// If the ghost is at the same location where pacman has moved, let the ghost stay
	// there and catch pacman!
	if (ghost_loc == pacman_loc) return ghost_loc;
	
    ObjectIdx selected1 = 0;
    unsigned min_dist = std::numeric_limits<unsigned>::max();
	
	unsigned _num_locations = _location.size(); // Locations are assumed to go between 1 and width*height
	// Collect the possible adjacent locations. Staying on the same loc is always an option
	std::vector<int> possible_locs;
	if (ghost_loc-_width > 0) possible_locs.push_back(ghost_loc-_width); // Move up
	if (ghost_loc-1 > 0) possible_locs.push_back(ghost_loc-1); // Move to the left
	possible_locs.push_back(ghost_loc); // Stay quiet
	if (ghost_loc+1 <= _num_locations) possible_locs.push_back(ghost_loc+1); // Move to the right
	if (ghost_loc+_width <= _num_locations) possible_locs.push_back(ghost_loc+_width); // Move down
	
	
    for (int loc : possible_locs) {
		// loc is, by definition, adjacent to ghost_loc
		assert(adjacent(ghost_loc, loc));
		
        if (_blocked.at(loc)) continue;

		unsigned dist = manhattan(loc, pacman_loc);
        if (dist < min_dist) {
            selected1 = loc;
            min_dist = dist;
        }
    }
    assert(min_dist != std::numeric_limits<unsigned>::max());

	/*
	ObjectIdx selected2 = 0;
	min_dist = std::numeric_limits<unsigned>::max();
	for ( auto loc : _location ) {
        if ( _blocked.at(loc) || !adjacent(ghost_loc, loc)) continue;

		unsigned dist = manhattan(loc, pacman_loc);
        if (dist < min_dist) {
            selected2 = loc;
            min_dist = dist;
        }
    }
    assert(min_dist != std::numeric_limits<unsigned>::max());
    
    assert(selected1 == selected2);
	*/
    
    LPT_DEBUG("pacman", "Ghost moves to location " << selected1 << " from " << ghost_loc );

    return selected1;
}

ObjectIdx
External::x(const std::vector<ObjectIdx>& arguments ) const {
    assert( arguments.size() == 1 );
    LPT_DEBUG("pacman", "x(args): argument: " << arguments[0] );
    LPT_DEBUG("pacman", "\t value: " << _location_x.at(arguments[0]) );
    return _location_x.at(arguments[0]);
}

ObjectIdx
External::y(const std::vector<ObjectIdx>& arguments ) const {
    assert( arguments.size() == 1 );
    LPT_DEBUG("pacman", "y(args): argument: " << arguments[0] );
    LPT_DEBUG("pacman", "\t value: " << _location_y.at(arguments[0]) );
    return _location_y.at(arguments[1]);
}

bool
External::valid_move(const std::vector<ObjectIdx>& arguments ) const {
	throw std::runtime_error("This shouldn't be invoked"); // we need to keep this for the moment being, silly as it is.
}

ObjectIdx
External::move_ghost(const State& state, const std::vector<ObjectIdx>& args ) const {
	return move_ghost(args);
}

ObjectIdx
External::x(const State& state, const std::vector<ObjectIdx>& args ) const {
    assert( args.size() == 1);
    return _location_x.at(args[0]);
}

ObjectIdx
External::y(const State& state, const std::vector<ObjectIdx>& args ) const {
    assert( args.size() == 1);
    return _location_y.at(args[0]);
}

bool
External::valid_move(const State& s, const std::vector<ObjectIdx>& args ) const {
    assert(args.size() == 2 );
	ObjectIdx from = args[0];
	ObjectIdx to = args[1];

	if (from == to) return true; // A no-op
    if ( _blocked.at(to) || !adjacent(from, to)) return false;

    return get_x(from) != get_x(to) || get_y(from) != get_y(to); // ???
}

MoveGhostTerm::MoveGhostTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@move_ghost" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 2);
}

MoveGhostTerm*
MoveGhostTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new MoveGhostTerm( subterms );
}

ObjectIdx
MoveGhostTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pacman", "Invoked MoveGhostTerm::compute()");
    return _external.move_ghost( state, arguments );
}

XTerm::XTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@x" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 1);
}

XTerm*
XTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new XTerm( subterms );
}

ObjectIdx
XTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pacman", "Invoked XTerm::compute()");
    return _external.x( state, arguments );
}

YTerm::YTerm( const std::vector< const fs::Term*>& subterms )
    : AxiomaticTerm( ProblemInfo::getInstance().getSymbolId( "@y" ), subterms ),
    _external( dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert( subterms.size() == 1);
}

YTerm*
YTerm::clone( const std::vector<const fs::Term*>& subterms) const {
    return new YTerm( subterms );
}

ObjectIdx
YTerm::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("pacman", "Invoked YTerm::compute()");
    return _external.y( state, arguments );
}

ValidMoveFormula::ValidMoveFormula( const std::vector<const fs::Term*>& subterms)
    : AxiomaticFormula(subterms),
    _external(dynamic_cast<const External&>(ProblemInfo::getInstance().get_external()))
{
    assert(subterms.size() == 2);
}

ValidMoveFormula*
ValidMoveFormula::clone(const std::vector<const fs::Term*>& subterms) const {
    return new ValidMoveFormula(subterms);
}

bool
ValidMoveFormula::compute(const State& state, std::vector<ObjectIdx>& arguments) const {
    LPT_DEBUG("predator_and_prey", "Invoked ValidMoveFormula::compute()");
    return _external.valid_move( state, arguments );
}
