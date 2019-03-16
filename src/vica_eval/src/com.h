/*
 * VICA
 * com.h
 *  Created on: 16 mars 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

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

#ifndef VICA_EVAL_SRC_COM_H_
#define VICA_EVAL_SRC_COM_H_

namespace vica_eval {

class com {
public:
	com(ros::NodeHandle n);
	virtual ~com();

	//env
	bool call_env_init();
	void call_env_get_size();;
	bool call_env_set_size(const int x, const int y);
	bool call_env_gui(const bool gui_on);
	bool call_env_stop();

	//agent
	bool call_agent_add();
	bool call_agent_delete(int id);
	bool call_agent_update();
	bool call_agent_get();
	bool call_agent_get_list();

	//sim
	bool call_sim_get_target_pos();
	bool call_sim_set_target_pos();
	bool call_sim_get_robot_pos();
	bool call_sim_start_sim();
	bool call_sim_get_sim_result();
	bool call_sim_reset_sim();



private:

	//ENV

	ros::ServiceClient cli_srv_vica_sim_env_init;
	ros::ServiceClient cli_srv_vica_sim_env_get_size;
	ros::ServiceClient cli_srv_vica_sim_env_set_size;
	ros::ServiceClient cli_srv_vica_sim_env_gui;
	ros::ServiceClient cli_srv_vica_sim_env_stop;

	//agent
	ros::ServiceClient cli_srv_vica_sim_agent_add;
	ros::ServiceClient cli_srv_vica_sim_agent_delete;
	ros::ServiceClient cli_srv_vica_sim_agent_update;
	ros::ServiceClient cli_srv_vica_sim_agent_get;
	ros::ServiceClient cli_srv_vica_sim_agent_get_list;

	//sim
	ros::ServiceClient cli_srv_vica_sim_sim_get_target_pos;
	ros::ServiceClient cli_srv_vica_sim_sim_set_target_pos;
	ros::ServiceClient cli_srv_vica_sim_sim_get_robot_pos;
	ros::ServiceClient cli_srv_vica_sim_sim_start_sim;
	ros::ServiceClient cli_srv_vica_sim_sim_get_sim_result;
	ros::ServiceClient cli_srv_vica_sim_sim_reset_sim;

	ros::NodeHandle nh;

};

} /* namespace vica_eval */

#endif /* VICA_EVAL_SRC_COM_H_ */
