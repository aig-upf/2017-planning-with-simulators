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
    //! Updates position vector as in (x',y') = (x,y) + (dx,dy), checking for bounds
	ObjectIdx   update(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   update(const std::vector<ObjectIdx>& arguments ) const;

    //! Prey policy
    //! select p' adjacent to current position p s.t. min dist(p',q), predator in q
    //! distance is measured according to Manhattan Distance
    ObjectIdx   next_move(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   next_move(const std::vector<ObjectIdx>& arguments ) const;

    //! Trapped predicate
    //! True if prey in same location as any of the predators
    bool   trapped(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    bool   trapped(const std::vector<ObjectIdx>& arguments ) const;

protected:

protected:

    //! Maps names of position vectors to their x and y coordinates.
    //! These guys are static.
    std::vector<ObjectIdx>                                      _positions;
    std::vector<ObjectIdx>                                      _predators;
    std::vector<ObjectIdx>                                      _preys;
    std::unordered_map<ObjectIdx,VariableIdx>                   _predator_location_vars;
    std::unordered_map<ObjectIdx,ObjectIdx>                     _x_position;
    std::unordered_map<ObjectIdx,ObjectIdx>                     _y_position;
    std::map<std::pair<ObjectIdx,ObjectIdx>, ObjectIdx> _xy2position;
    ObjectIdx                                                   _max_x;
    ObjectIdx                                                   _max_y;
    ObjectIdx                                                   _min_x;
    ObjectIdx                                                   _min_y;

    //! These are not
    //! Include locations of predators and preys
    mutable std::unordered_map<ObjectIdx,ObjectIdx>             _x_predator;
    mutable std::unordered_map<ObjectIdx,ObjectIdx>             _y_predator;
    mutable std::unordered_map<ObjectIdx,ObjectIdx>             _x_prey;
    mutable std::unordered_map<ObjectIdx,ObjectIdx>             _y_prey;
    mutable std::unordered_map<ObjectIdx,int>                   _distance_to_predator;
};

class UpdateTerm : public fs::AxiomaticTerm {
public:
    UpdateTerm( const std::vector<const fs::Term*>& subterms );

	UpdateTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "update"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};

class NextMoveTerm : public fs::AxiomaticTerm {
public:
    NextMoveTerm( const std::vector<const fs::Term*>& subterms );

	NextMoveTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "next_move"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};

class TrappedFormula : public fs::AxiomaticFormula {
public:

    TrappedFormula( const std::vector<const fs::Term*>& subterms);

    TrappedFormula* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "trapped"; };

	bool compute(const State& state, std::vector<ObjectIdx>& arguments) const override;

protected:

    const External& _external;

};
