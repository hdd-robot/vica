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


void path_graph::set_goal(double x, double y) {
	this->goal = std::complex<double>(x,y);
}


vertex_t path_graph::add_node(double teta1, double teta2, double dist1, double dist2 ) {

	bool insert(true);
	std::complex<double> new_point_1 = std::polar(dist1,teta1) + get_pos_robot();
	std::complex<double> new_point_2 = std::polar(dist2,teta2) + get_pos_robot();

	std::pair<vertex_iter, vertex_iter> vp;

	for (vp = boost::vertices(this->g); vp.first != vp.second; ++vp.first) {
		VertexProperties tmp_vtx = g[*(vp.first)];
		double dt ;
		dt = get_euclidean_distance(new_point_1, std::complex<double>(std::polar(tmp_vtx.dist_teta_1,tmp_vtx.teta_1)));
		if (dt < 0.2){
			insert = false;
			break;
		}

		dt = get_euclidean_distance(new_point_2, std::complex<double>(std::polar(tmp_vtx.dist_teta_2,tmp_vtx.teta_2)));
		if (dt < 0.2){
			insert = false;
			break;
		}
	}

	vertex_t vtx;

	if (insert == true){

		bool visited = false;
		double goal_dist_1 = abs(new_point_1 - this->goal) ;
		double goal_dist_2 = abs(new_point_2 - this->goal) ;
		double dst_1  = abs(std::polar(dist1,teta1));
		double dst_2  = abs(std::polar(dist2,teta2));

		vtx = boost::add_vertex(VertexProperties(count,teta1, teta2,dst_1,dst_2,goal_dist_1,goal_dist_2,visited), g);
		if(count != 0){
			std::pair<Graph::edge_descriptor, bool> edg = boost::add_edge(this->head_vertex,vtx,EdgeProperties(1,1),this->g);
		}

		count ++;
	}

	return vtx;

}

void path_graph::set_init_node() {

	this->init_vertex = add_node(0,0,0,0);
	this->head_vertex = init_vertex;
}

double path_graph::get_euclidean_distance_goal(std::complex<double> pos) {
	return path_graph::get_euclidean_distance(this->goal, pos);
}

double path_graph::get_euclidean_distance(std::complex<double> pos1, std::complex<double> pos2) {
	std::complex<double> dt = pos1 - pos2;
	return abs(dt);
}

std::complex<double> path_graph::get_pos_robot() {
	std::complex<double> r_pos(0,0);
	return r_pos;
}

void path_graph::draw_graph() {
	std::ofstream dmp;
	dmp.open("/home/ros/workspace_vica/src/vica_eval_graph/graph/dmp_graph_path.dot");
	boost::write_graphviz(dmp,g,make_label_writer(get(&VertexProperties::id,g)));
}

std::complex<double> path_graph::get_netx_pos() {


	std::complex<double> best_next_pox = get_pos_robot();
	VertexProperties best_vertex_tmp;


	for (std::pair<adja_iter, adja_iter> vp = boost::adjacent_vertices(this-> head_vertex,this->g); vp.first != vp.second; ++vp.first) {
		VertexProperties tmp_vtx = g[*(vp.first)];
		ROS_INFO(" -- id :  %d ", tmp_vtx.id);
	}



	return best_next_pox;
}

} /* namespace vica_eval */
















