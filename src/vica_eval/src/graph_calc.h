/*
 * VICA
 * graph_calc.h
 *  Created on: 14 mars 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <string>

#ifndef VICA_EVAL_SRC_GRAPH_CALC_H_
#define VICA_EVAL_SRC_GRAPH_CALC_H_

namespace vica_eval {

using namespace std;



struct VertexProperties
{
   std::string name;
   unsigned id;
   VertexProperties() : name(""), id(0) {}
   VertexProperties(std::string const& n, unsigned i) : name(n), id(i) {}
};

struct EdgeProperties
{
   float weight;
   float distance;
   EdgeProperties() : weight(0.0), distance(0.0) {}
   EdgeProperties(float w, float d) : weight(w), distance(d) {}
};

struct GraphProperties {
};

typedef boost::adjacency_list<
   boost::vecS, boost::vecS, boost::bidirectionalS,
   VertexProperties, EdgeProperties,GraphProperties
> Graph;

typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;



class graph_calc {
public:
	graph_calc();

	virtual ~graph_calc();


	Graph g;

};

} /* namespace vica_eval */

#endif /* VICA_EVAL_SRC_GRAPH_CALC_H_ */
