#include "ros/ros.h"
#include <vica_sim/vica_sim_env_gui.h>

#include "graph_calc.h"


namespace vica_eval {

}

using namespace vica_eval;

int main(int argc, char *argv[]) {

	ros::init(argc, argv, "vica_eval");

	ros::NodeHandle n;
	ros::Rate loop_rate(10);

	ros::ServiceClient client = n.serviceClient<vica_sim::vica_sim_env_gui>("/vica_sim/env/gui");

	vica_sim::vica_sim_env_gui srv;

	srv.request.gui = true;

	if (client.call(srv)) {
		ROS_INFO("Resultat GUI : %d", srv.response.res);
	} else {
		ROS_ERROR("Failed to call service GUI");
		return 1;
	}


	graph_calc gcalc;





	while (ros::ok()) {

		ros::spinOnce();
		loop_rate.sleep();
	}

}
