#include "ros/ros.h"

#include "vica_sim/vica_sim_env_init.h"
#include "vica_sim/vica_sim_env_get_size.h"
#include "vica_sim/vica_sim_env_set_size.h"
#include "vica_sim/vica_sim_env_gui.h"

#include "sma_img.h"


using namespace vica_sim;

namespace vica_sim {

SMA_Img* sma = new SMA_Img();


bool srv_init(vica_sim::vica_sim_env_init::Request &req,
			  vica_sim::vica_sim_env_init::Response &res) {
//  ROS_INFO("request: action=%s, param=%s", req.action, req.param);
//  ROS_INFO("sending back response: [%d]", 1 );
//  res.res = 50;
	sma->add_agent();

	ROS_INFO("srv_init");

	return true;
}

bool srv_get_size(vica_sim::vica_sim_env_get_size::Request &req,
				  vica_sim::vica_sim_env_get_size::Response &res) {

	ROS_INFO("srv_get_size");
	return true;
}

bool srv_set_size(vica_sim::vica_sim_env_set_size::Request &req,
				  vica_sim::vica_sim_env_set_size::Response &res) {

	ROS_INFO("srv_set_size");
	return true;
}

bool srv_gui(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("srv_gui");
	return true;
}

}

int main(int argc, char *argv[]) {



	//

	ros::init(argc, argv, "vica_sim");
	ros::NodeHandle n;

	//ENV
	ros::ServiceServer env_srv_1 = n.advertiseService("/vica_sim/env/init"	  , srv_init);
	ros::ServiceServer env_srv_2 = n.advertiseService("/vica_sim/env/get_size", srv_get_size);
	ros::ServiceServer env_srv_3 = n.advertiseService("/vica_sim/env/set_size",	srv_set_size);
	ros::ServiceServer env_srv_4 = n.advertiseService("/vica_sim/env/gui"     ,	srv_gui);

	ROS_INFO("Ready to add two ints.");


	ros::spin();


	ROS_INFO("Fin spin.");


	return 0;
}

















