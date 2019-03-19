#include "ros/ros.h"

#include <iostream>
#include <vica_sim/vica_sim_env_gui.h>
#include "com.h"
#include "graph_calc.h"
#include "object_type.h"

namespace vica_eval {

}

using namespace vica_eval;

int main(int argc, char *argv[]) {

	ros::init(argc, argv, "vica_eval");

	ros::NodeHandle nh;
	com cm(nh);

	object_type::load_csv_file("/home/ros/workspace_vica/src/vica_eval/data/dada_scen_1.csv");



	cm.call_env_gui(true);

	//load objct from CSV

	object_type *obj1 = new object_type();
	while(obj1->load_next_object()){
		cm.call_agent_add(obj1);
	}

	//create graph
	graph_calc gcalc;


	ros::Rate loop_rate(10);
	while (ros::ok()) {




		ros::spinOnce();
		loop_rate.sleep();
	}

}
