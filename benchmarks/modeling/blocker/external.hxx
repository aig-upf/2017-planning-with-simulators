#pragma once

#include <vector>
#include <unordered_map>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <lapkt/tools/logging.hxx>
#include <problem_info.hxx>
#include <utils/external.hxx>
#include <languages/fstrips/builtin.hxx>
#include <languages/fstrips/terms.hxx>
#include <state.hxx>

namespace fs = fs0::language::fstrips;
using namespace fs0;

class External : public fs0::ExternalI {

    typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::bidirectionalS, boost::no_property, boost::property < boost::edge_weight_t, int > > Graph;
    typedef boost::graph_traits < Graph >::vertex_descriptor Vertex;
    typedef std::pair< ObjectIdx, ObjectIdx >   Edge;

public:

    External( const ProblemInfo& info, const std::string& data_dir ) ;
    ~External();

    void registerComponents() const;

    //! Procedurally defined symbols
    //! ;; (trapped) is true iff the cat is trapped; that is, distance-to-exit
    //! ;; is false for every value from the cat's current position.
    //! (:derived (trapped)
    //!       (exists (?x)
    //!           (and (cat ?x)
    //!            (forall (?n) (not (distance-to-exit ?x ?n))))))
	bool        trapped( const State& state, const std::vector<ObjectIdx>& arguments ) const;
    bool        trapped(  const std::vector<ObjectIdx>& arguments ) const;

    //! ;; (cat-moves ?from ?to) iff ?to is the node that the cat will move to
    //! ;; from ?from. This is the node that is closest to an exit, or least
    //! ;; among the nodes the minimum distance to exit. If the cat is already
    //! ;; trapped, this predicate is false for all destinations.
    //! (:derived (cat-moves ?from ?to)
  	//!     (and (edge ?from ?to)
  	//! 	 (not (blocked ?to))
  	//! 	 (not (trapped))
  	//! 	 (forall (?alt)
  	//! 		 (or (= ?to ?alt)
  	//! 		     (not (edge ?from ?alt))
  	//! 		     (prefer ?to ?alt)))))

	ObjectIdx   cat_moves(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   cat_moves(const std::vector<ObjectIdx>& arguments ) const;


    //! Actual distance to exit
    //! computes the distance to the exit for the node the cat will move to,
    //! given the current state
    ObjectIdx    distance_to_exit( const State& s, const std::vector<ObjectIdx>& arguments  ) const;
    ObjectIdx    distance_to_exit( const std::vector<ObjectIdx>& arguments  ) const;

    bool        can_block( const State& state, const std::vector<ObjectIdx>& arguments ) const;
    bool        can_block(  const std::vector<ObjectIdx>& arguments ) const;


    //! Original derived predicate by P. Haslum
    //! ;; (prefer ?x ?y) iff cat prefers moving to ?x over ?y (only
    //! ;; relevant if ?x and ?y are both neighbours of the cat's current
    //! ;; position, but this is not tested for here). This is true if ?y
    //! ;; is blocked; ?x is strictly closer to an exit than ?y; or ?x and
    //! ;; ?y are at the same distance to exit but ?x is less than ?y (i.e.,
    //! ;; numeric order of the nodes is used as the final tie-breaker).
    //! (:derived (prefer ?x ?y)
    //!       (or (blocked ?y)
    //!       (closer-to-exit ?x ?y)
    //!       (and (closer-or-equal-to-exit ?x ?y)
    //!            (less ?x ?y))))
    bool    prefer( const State& s,  const std::vector<ObjectIdx>& arguments ) const;


    //! Original derived predicate by P. Haslum
    //! ;; (closer-or-equal-to-exit ?x ?y) holds if the shortest distance to
    //! ;; an exit from ?x is less than or equal to the shortest distance to
    //! ;; an exit from ?y.
    //! (:derived (closer-or-equal-to-exit ?x ?y)
    //!       (not (closer-to-exit ?y ?x)))

    bool        closer_or_equal_to_exit( const State& s, const std::vector<ObjectIdx>& arguments ) const;

    //! Original derived predicate by P. Haslum
    //! ;; (closer-to-exit ?x ?y) holds if the shortest distance to an exit
    //! ;; from ?x is stricly smaller than the shortest distance to an exit
    //! ;; from ?y.
    //! (:derived (closer-to-exit ?x ?y)
    //!       (exists (?k)
    //!           (and (distance-to-exit ?x ?k)
    //!            (not (distance-to-exit ?y ?k)))))
    //!

    bool        closer_to_exit( const State& s, const std::vector<ObjectIdx>& arguments ) const;

protected:
    //! MRJ: We need to update the graph because the
    //! "blocker" agent changes its topology via the
    //! block(n) action.
    //! TODO - consider caching? depending on values of blocked(n) state vars
    void        update_graph( const State& s ) const;

protected:

    const ObjectIdx                                             _nowhere;
    const std::vector<ObjectIdx>                                _nodes;
    std::vector<ObjectIdx>                                      _exit_nodes;
    std::vector<unsigned>                                       _exit_nodes_idx;
    std::unordered_map<ObjectIdx,bool>                          _is_exit;
    std::unordered_map<ObjectIdx,VariableIdx>                   _blocked_vars;
    mutable std::unordered_map<ObjectIdx,bool>                  _blocked;
    mutable Graph                                               _maze;
    mutable std::unordered_map<ObjectIdx,unsigned>              _distance_to_exit;
    std::vector<Edge>                                           _edges;
    VariableIdx                                                 _cat_var;
    unsigned                                                    _edge_pred_sym;
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

class CanBlockFormula : public fs::AxiomaticFormula {
public:

    CanBlockFormula( const std::vector<const fs::Term*>& subterms);

    CanBlockFormula* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "can_block"; };

	bool compute(const State& state, std::vector<ObjectIdx>& arguments) const override;

protected:

    const External& _external;

};

class CatMovesTerm : public fs::AxiomaticTerm {
public:
    CatMovesTerm( const std::vector<const fs::Term*>& subterms );

	CatMovesTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "cat_moves"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};

class DistanceToExitTerm : public fs::AxiomaticTerm {
public:
    DistanceToExitTerm( const std::vector<const fs::Term*>& subterms );

	DistanceToExitTerm* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "distance_to_exit"; };

	ObjectIdx compute(const State& state, std::vector<ObjectIdx>& arguments) const override;
protected:

    const External& _external;
};
