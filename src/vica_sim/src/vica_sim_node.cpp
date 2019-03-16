#include "ros/ros.h"



//env
#include <vica_sim/vica_sim_env_init.h>
#include <vica_sim/vica_sim_env_get_size.h>
#include <vica_sim/vica_sim_env_set_size.h>
#include <vica_sim/vica_sim_env_gui.h>
#include <vica_sim/vica_sim_env_stop.h>

//agent
#include <vica_sim/vica_sim_agent_add.h>
#include <vica_sim/vica_sim_agent_delete.h>
#include <vica_sim/vica_sim_agent_update.h>
#include <vica_sim/vica_sim_agent_get.h>
#include <vica_sim/vica_sim_agent_get_list.h>

//sim
#include <vica_sim/vica_sim_sim_get_target_pos.h>
#include <vica_sim/vica_sim_sim_set_target_pos.h>
#include <vica_sim/vica_sim_sim_get_robot_pos.h>
#include <vica_sim/vica_sim_sim_start_sim.h>
#include <vica_sim/vica_sim_sim_get_sim_result.h>
#include <vica_sim/vica_sim_sim_reset_sim.h>

#include "sma_img.h"


using namespace vica_sim;

namespace vica_sim {

SMA_Img* sma = new SMA_Img();


bool env_init(vica_sim::vica_sim_env_init::Request &req,
			  vica_sim::vica_sim_env_init::Response &res) {
//  ROS_INFO("request: action=%s, param=%s", req.action, req.param);
//  ROS_INFO("sending back response: [%d]", 1 );
//  res.res = 50;
	sma->add_agent();

	ROS_INFO("srv_init");

	return true;
}

//env

bool env_get_size(vica_sim::vica_sim_env_get_size::Request &req,
				  vica_sim::vica_sim_env_get_size::Response &res) {

	ROS_INFO("srv_get_size");
	return true;
}

bool env_set_size(vica_sim::vica_sim_env_set_size::Request &req,
				  vica_sim::vica_sim_env_set_size::Response &res) {

	ROS_INFO("srv_set_size");
	return true;
}

bool env_gui(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("srv_gui");
	return true;
}

bool env_stop(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("env_stop");
	return true;
}

//agent

bool agent_add(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("agent_add");
	return true;
}

bool agent_delete(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("agent_delete");
	return true;
}

bool agent_update(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("agent_update");
	return true;
}

bool agent_get(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("agent_get");
	return true;
}

bool agent_get_list(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("agent_get_list");
	return true;
}


//sim
bool sim_get_target_pos(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("sim_get_target_pos");
	return true;
}


bool sim_set_target_pos(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("sim_set_target_pos");
	return true;
}

bool sim_get_robot_pos(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("sim_get_robot_pos");
	return true;
}


bool sim_start_sim(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("sim_start_sim");
	return true;
}

bool sim_get_sim_restult(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("sim_get_sim_restult");
	return true;
}


bool sim_reset_sim(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("sim_reset_sim");
	return true;
}


}

int main(int argc, char *argv[]) {



	//

	ros::init(argc, argv, "vica_sim");
	ros::NodeHandle n;

	//ENV
	ros::ServiceServer env_srv_1 = n.advertiseService("/vica_sim/env/init"	  , env_init);
	ros::ServiceServer env_srv_2 = n.advertiseService("/vica_sim/env/get_size", env_get_size);
	ros::ServiceServer env_srv_3 = n.advertiseService("/vica_sim/env/set_size",	env_set_size);
	ros::ServiceServer env_srv_4 = n.advertiseService("/vica_sim/env/gui"     ,	env_gui);
	ros::ServiceServer env_srv_5 = n.advertiseService("/vica_sim/env/stop"    ,	env_stop);

	//agent
	ros::ServiceServer agent_srv_1 = n.advertiseService("/vica_sim/agent/add"	  , agent_add);
	ros::ServiceServer agent_srv_2 = n.advertiseService("/vica_sim/agent/delete"  , agent_delete);
	ros::ServiceServer agent_srv_3 = n.advertiseService("/vica_sim/agent/update"  , agent_update);
	ros::ServiceServer agent_srv_4 = n.advertiseService("/vica_sim/agent/get"	  , agent_get);
	ros::ServiceServer agent_srv_5 = n.advertiseService("/vica_sim/agent/get_list", agent_get_list);

	//sim
	ros::ServiceServer sim_srv_1 = n.advertiseService("/vica_sim/sim/get_target_pos", sim_get_target_pos);
	ros::ServiceServer sim_srv_2 = n.advertiseService("/vica_sim/sim/set_target_pos", sim_set_target_pos);
	ros::ServiceServer sim_srv_3 = n.advertiseService("/vica_sim/sim/get_robot_pos"	, sim_get_robot_pos);
	ros::ServiceServer sim_srv_4 = n.advertiseService("/vica_sim/sim/start_sim"	  	, sim_start_sim);
	ros::ServiceServer sim_srv_5 = n.advertiseService("/vica_sim/sim/get_sim_result", sim_get_sim_restult);
	ros::ServiceServer sim_srv_6 = n.advertiseService("/vica_sim/sim/reset_sim"	  	, sim_reset_sim);



	//sim




	ROS_INFO("Ready to add two ints.");


	ros::spin();


	ROS_INFO("Fin spin.");


	return 0;
}

















