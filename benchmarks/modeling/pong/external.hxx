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
    //! Calculates the deflected velocity vector of the puck when it collides with a
    //! given obstacle
	ObjectIdx   deflect(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   deflect(const std::vector<ObjectIdx>& arguments ) const;

    //! Implements function clamp(x,lb,ub) := max( lb, min( x, ub))
    ObjectIdx   clamp(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   clamp(const std::vector<ObjectIdx>& arguments ) const;

    //! Accelerates the puck depending on the direction of movement of the paddle
    ObjectIdx   accelerate(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   accelerate(const std::vector<ObjectIdx>& arguments ) const;

    //! Determines whether there is a collision of the puck with an obstacle
    bool   collision(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    bool   collision(const std::vector<ObjectIdx>& arguments ) const;

    //! Determines whether the game is still on or not
    bool   game_on(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    bool   game_on(const std::vector<ObjectIdx>& arguments ) const;

    //! Determines whether there is a collision of the puck with an obstacle
    bool   not_collision(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    bool   not_collision(const std::vector<ObjectIdx>& arguments ) const;

    //! Computes the sum of hits with the paddle
    ObjectIdx   sum_hits(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   sum_hits(const std::vector<ObjectIdx>& arguments ) const;

    //! Distance to paddle
    ObjectIdx   distance_to_paddle(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   distance_to_paddle(const std::vector<ObjectIdx>& arguments ) const;

    //! Get puck pixel
    ObjectIdx   get_puck_pixel(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   get_puck_pixel(const std::vector<ObjectIdx>& arguments ) const;
protected:

    //! These guys are static
    std::vector<ObjectIdx>                                  _puck;
    ObjectIdx                                               _top;
    ObjectIdx                                               _bottom;
    ObjectIdx                                               _left;
    ObjectIdx                                               _right;
    ObjectIdx                                               _paddle;
    ObjectIdx                                               _paddle_obs;
    ObjectIdx                                               _paddle_radius;
    std::vector<ObjectIdx>                                  _velocities;

    std::unordered_map<ObjectIdx,ObjectIdx>                 _vx;
    std::unordered_map<ObjectIdx,ObjectIdx>                 _vy;
    std::map<std::pair<ObjectIdx,ObjectIdx>, ObjectIdx>     _vxvy2vector;

    //! Maps obstacles to bounds values
    std::unordered_map<ObjectIdx,ObjectIdx>                 _obs_bound;

    std::unordered_map<ObjectIdx,VariableIdx>               _x_puck_var;
    std::unordered_map<ObjectIdx,VariableIdx>               _y_puck_var;
    std::unordered_map<ObjectIdx,VariableIdx>               _a_puck_var;
    std::unordered_map<ObjectIdx,VariableIdx>               _v_puck_var;
    std::unordered_map<ObjectIdx,VariableIdx>               _hits_var;
    VariableIdx                                             _paddle_center_var;
    VariableIdx                                             _paddle_prev_dy_var;
    VariableIdx                                             _current_mode_var;

protected:

};

class DeflectTerm : public fs::AxiomaticTerm {
public:
    DeflectTerm( const std::vector<const fs::Term*>& subterms );

	DeflectTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "deflect"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};

class ClampTerm : public fs::AxiomaticTerm {
public:
    ClampTerm( const std::vector<const fs::Term*>& subterms );

	ClampTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "clamp"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};

class AccelerateTerm : public fs::AxiomaticTerm {
public:
    AccelerateTerm( const std::vector<const fs::Term*>& subterms );

	AccelerateTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "accelerate"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};

class CollisionFormula : public fs::AxiomaticFormula {
public:

    CollisionFormula( const std::vector<const fs::Term*>& subterms);

    CollisionFormula* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "collision"; };

	bool compute(const State& state, std::vector<ObjectIdx>& arguments) const override;

protected:

    const External& _external;

};


class NotCollisionFormula : public fs::AxiomaticFormula {
public:

    NotCollisionFormula( const std::vector<const fs::Term*>& subterms);

    NotCollisionFormula* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "not_collision"; };

	bool compute(const State& state, std::vector<ObjectIdx>& arguments) const override;

protected:

    const External& _external;

};

class GameOnFormula : public fs::AxiomaticFormula {
public:

    GameOnFormula( const std::vector<const fs::Term*>& subterms);

    GameOnFormula* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "game_on"; };

	bool compute(const State& state, std::vector<ObjectIdx>& arguments) const override;

protected:

    const External& _external;

};

class SumHitsTerm : public fs::AxiomaticTerm {
public:
    SumHitsTerm( const std::vector<const fs::Term*>& subterms );

	SumHitsTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "sum_hits"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};

class DistanceToPaddleTerm : public fs::AxiomaticTerm {
public:
    DistanceToPaddleTerm( const std::vector<const fs::Term*>& subterms );

	DistanceToPaddleTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "distance_to_paddle"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};

class GetPuckPixelTerm : public fs::AxiomaticTerm {
public:
    GetPuckPixelTerm( const std::vector<const fs::Term*>& subterms );

	GetPuckPixelTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "get_puck_pixel"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};
