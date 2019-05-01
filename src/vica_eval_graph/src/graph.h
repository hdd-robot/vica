
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <utility>
#include <algorithm>
#include <complex>

#ifndef WORK_GRAPH_VISIBLE_SRC_GRAPH_H_
#define WORK_GRAPH_VISIBLE_SRC_GRAPH_H_

namespace vica_eval {










struct VertexProperties
{
	unsigned id;
	double teta_1;
	double teta_2;
	double dist_teta_1;
	double dist_teta_2;
	bool visited = false;
	double direct_goal_distance = 0;
	VertexProperties() : id(0), teta_1(0), teta_2(0),dist_teta_1(0), dist_teta_2(0) {}
	VertexProperties(unsigned i,double t1, double t2,double dt1,double dt2, double dir_dist, bool vstd) :
			id(i), teta_1(t1), teta_2(t2), dist_teta_1(t2), dist_teta_2(dt2), direct_goal_distance(dir_dist), visited(vstd) {}
};

struct EdgeProperties
{
	double weight;
	double distance;
	EdgeProperties() : weight(0.0), distance(0.0) {}
	EdgeProperties(double w, double d) : weight(w), distance(d) {}
};

struct GraphProperties {
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
		VertexProperties, EdgeProperties, GraphProperties> Graph;

typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;

typedef boost::graph_traits<Graph>::adjacency_iterator adja_iter;



class path_graph {
public:
	path_graph();
	virtual ~path_graph();

	void set_init_node();

	double get_euclidean_distance_goal(std::complex<double> pos);
	double get_euclidean_distance(std::complex<double> pos1, std::complex<double> pos2);
	std::complex<double> get_pos_robot();

	void clear_grap();

	vertex_t add_node(double tet1, double tet2, double x, double y);

	void set_goal(double, double );

	void draw_graph();

	void get_netx_pos();

	Graph g;
	int count = 0;



	std::complex<double> goal;

	vertex_t init_vertex;
	vertex_t head_vertex;
};

} /* namespace vica_eval */

#endif /* WORK_GRAPH_VISIBLE_SRC_GRAPH_H_ */



