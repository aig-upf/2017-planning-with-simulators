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
    //! Cat moves towards the closest location which is lighted up
	ObjectIdx   cat_moves(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   cat_moves(const std::vector<ObjectIdx>& arguments ) const;


    //! Procedurally defined symbols
    //! Returns the sum of distances to the closest exit for each of the cats
	ObjectIdx   distance_to_exit(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    ObjectIdx   distance_to_exit(const std::vector<ObjectIdx>& arguments ) const;


    bool   can_view(const State& state, const std::vector<ObjectIdx>& arguments ) const;
    bool   can_view(const std::vector<ObjectIdx>& arguments ) const;

protected:
    //! MRJ: We need to update the graph because the
    //! "blocker" agent changes its topology via the
    //! block(n) action.
    //! TODO - consider caching? depending on values of blocked(n) state vars
    void        update_graph( const State& s ) const;

protected:

    ObjectIdx                                                   _nowhere;
    std::vector<ObjectIdx>                                      _nodes;
    std::vector<ObjectIdx>                                      _light_nodes;
    std::vector<ObjectIdx>                                      _cats;
    std::vector<unsigned>                                       _light_nodes_idx;
    std::unordered_map<ObjectIdx,bool>                          _is_exit;
    std::unordered_map<ObjectIdx,VariableIdx>                   _light_vars;
    std::unordered_map<ObjectIdx,VariableIdx>                   _cat_location_vars;
    std::unordered_map<ObjectIdx,ObjectIdx>                     _cat_view_ranges;
    std::map<std::pair<ObjectIdx,ObjectIdx>,ObjectIdx>          _distance;
    Graph                                                       _map;
    mutable std::unordered_map<ObjectIdx,int>                   _distance_to_exit;

    mutable std::unordered_map<ObjectIdx,bool>                  _alight;
    mutable std::unordered_map<ObjectIdx,int>                   _distance_to_light;
    mutable std::unordered_map<ObjectIdx,ObjectIdx>             _cat_location;
};

class CanViewFormula : public fs::AxiomaticFormula {
public:

    CanViewFormula( const std::vector<const fs::Term*>& subterms);

    CanViewFormula* clone(const std::vector<const fs::Term*>& subterms) const override;

    std::string name() const override { return "can_view"; };

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
