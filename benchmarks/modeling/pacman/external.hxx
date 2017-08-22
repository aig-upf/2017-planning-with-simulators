#pragma once

#include <vector>
#include <unordered_map>

#include <lapkt/tools/logging.hxx>
#include <problem_info.hxx>
#include <utils/external.hxx>
#include <languages/fstrips/builtin.hxx>
#include <languages/fstrips/terms.hxx>
#include <state.hxx>

namespace fs = fs0::language::fstrips;
using namespace fs0;

class External : public fs0::ExternalI {

public:

    External( const ProblemInfo& info, const std::string& data_dir ) ;
    ~External();

    void registerComponents() const;

    //! Procedurally defined symbols
    //! initial location of objects
	ObjectIdx   initial_location(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   initial_location(const std::vector<ObjectIdx>& arguments ) const;

    //! initial number of pellets at a given location
    ObjectIdx   initial_num_pellets(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   initial_num_pellets(const std::vector<ObjectIdx>& arguments ) const;

    //! move_ghost(?g)
    //! deterministic policy that determines the location the ghost will move
    ObjectIdx   move_ghost(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   move_ghost(const std::vector<ObjectIdx>& arguments ) const;

    //! x(?o) - x coordinate of an object
    ObjectIdx  x(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx  x(const std::vector<ObjectIdx>& arguments ) const;

    //! y(?o) - y coordinate of an object
    ObjectIdx  y(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx  y(const std::vector<ObjectIdx>& arguments ) const;
    
    //! valid_move(?l)
    //! whether location ?l is valid_move from the current location of the pacman
    bool  valid_move(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    bool  valid_move(const std::vector<ObjectIdx>& arguments ) const;


protected:

    int     get_x( ObjectIdx o ) const { return _location_x.at(o); }//return boost::get<int>( _location_x.at(o) ); }
    int     get_y( ObjectIdx o ) const { return _location_y.at(o); }//return boost::get<int>( _location_y.at(o) ); }

    unsigned manhattan( ObjectIdx src, ObjectIdx dst ) const {
        return std::abs( get_x(src) - get_x(dst) ) + std::abs( get_y(src) - get_y(dst) );
    }

    bool     adjacent( ObjectIdx src, ObjectIdx dst ) const {
        return manhattan(src,dst) <= 1;
    }

protected:

    //! These guys are static.
    std::vector<ObjectIdx>                                      _pacman;
    std::vector<ObjectIdx>                                      _ghost;
    std::vector<ObjectIdx>                                      _location;
    std::unordered_map<ObjectIdx,ObjectIdx>                     _location_x;
    std::unordered_map<ObjectIdx,ObjectIdx>                     _location_y;
    std::unordered_map<ObjectIdx,bool>                          _blocked;
	
	unsigned _width; // The width of the map
};



class MoveGhostTerm : public fs::AxiomaticTerm {
public:
    MoveGhostTerm( const std::vector<const fs::Term*>& subterms );

	MoveGhostTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "move_ghost"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};

class XTerm : public fs::AxiomaticTerm {
public:
    XTerm( const std::vector<const fs::Term*>& subterms );

	XTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "x"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};

class YTerm : public fs::AxiomaticTerm {
public:
    YTerm( const std::vector<const fs::Term*>& subterms );

	YTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "y"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};

class ValidMoveFormula : public fs::AxiomaticFormula {
public:

    ValidMoveFormula( const std::vector<const fs::Term*>& subterms);

    ValidMoveFormula* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "valid_move"; };

	bool compute(const State& state, std::vector<ObjectIdx>& arguments) const override;

protected:

    const External& _external;

};
