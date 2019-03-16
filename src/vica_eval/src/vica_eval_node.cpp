#include "ros/ros.h"
#include <vica_sim/vica_sim_env_gui.h>

#include "com.h"
#include "graph_calc.h"


namespace vica_eval {

}

using namespace vica_eval;

int main(int argc, char *argv[]) {

	ros::init(argc, argv, "vica_eval");

	ros::NodeHandle nh;

	com cm(nh);


	cm.call_env_gui(true);

	cm.call_agent_add();

	graph_calc gcalc;


	ros::Rate loop_rate(10);
	while (ros::ok()) {




		ros::spinOnce();
		loop_rate.sleep();
	}

}
