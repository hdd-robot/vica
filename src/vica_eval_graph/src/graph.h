
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>


#ifndef WORK_GRAPH_VISIBLE_SRC_GRAPH_H_
#define WORK_GRAPH_VISIBLE_SRC_GRAPH_H_

namespace vica_eval {


struct VertexProperties
{
	unsigned id;
	float teta_1;
	float teta_2;
	bool visited = false;
	float direct_goal_distance = 0;
	VertexProperties() : id(0), teta_1(0), teta_2(0) {}
	VertexProperties(unsigned i, float t1, float t2) : id(i),teta_1(t1), teta_2(t2) {}
	VertexProperties(unsigned i, float t1, float t2, float dir_dist, bool vstd) :
			id(i), teta_1(t1), teta_2(t2), direct_goal_distance(dir_dist), visited(vstd) {}
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

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
		VertexProperties, EdgeProperties, GraphProperties> Graph;

typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;



class path_graph {
public:
	path_graph();
	virtual ~path_graph();

	void clear_grap();

	void add_vertex(float,float);

	void set_goal(float, float );

	void draw_graph();

	Graph g;
	int count = 0;

	float goal_x;
	float goal_y;

};

} /* namespace vica_eval */

#endif /* WORK_GRAPH_VISIBLE_SRC_GRAPH_H_ */



