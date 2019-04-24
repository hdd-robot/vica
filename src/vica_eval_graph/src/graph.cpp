/*
 * VICA
 * graph.cpp
 *  Created on: 9 avr. 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#include "graph.h"

namespace vica_eval {

path_graph::path_graph() {

}

path_graph::~path_graph() {

}


void path_graph::clear_grap() {
	g.clear();
}


void path_graph::set_goal(float x, float y) {
	this->goal_x = x;
	this->goal_y = y;
}


void path_graph::add_vertex(float tet1, float tet2) {
	vertex_t vtx = boost::add_vertex(VertexProperties(count, tet1, tet2), g);
	count ++;

}



void path_graph::draw_graph() {
	std::ofstream dmp;
	dmp.open("/home/ros/workspace_vica/src/vica_eval_graph/graph/dmp_graph_path.dot");
	boost::write_graphviz(dmp,g);
}



} /* namespace vica_eval */

