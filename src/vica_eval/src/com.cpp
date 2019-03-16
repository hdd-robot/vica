/*ros::NodeHandle
 * VICA
 * com.cpp
 *  Created on: 16 mars 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#include "com.h"

namespace vica_eval {



com::com(ros::NodeHandle n) {
	nh = n;

	//ENV
	cli_srv_vica_sim_env_init = nh.serviceClient<vica_sim::vica_sim_env_init>("/vica_sim/env/init");
	cli_srv_vica_sim_env_get_size = nh.serviceClient<vica_sim::vica_sim_env_get_size>("/vica_sim/env/get_size");
	cli_srv_vica_sim_env_set_size = nh.serviceClient<vica_sim::vica_sim_env_set_size>("/vica_sim/env/set_size");
	cli_srv_vica_sim_env_gui = nh.serviceClient<vica_sim::vica_sim_env_gui>("/vica_sim/env/gui");
	cli_srv_vica_sim_env_stop = nh.serviceClient<vica_sim::vica_sim_env_stop>("/vica_sim/env/stop");

	//agent
	cli_srv_vica_sim_agent_add = nh.serviceClient<vica_sim::vica_sim_agent_add>("/vica_sim/agent/add");
	cli_srv_vica_sim_agent_delete = nh.serviceClient<vica_sim::vica_sim_agent_delete>("/vica_sim/agent/delete");
	cli_srv_vica_sim_agent_update = nh.serviceClient<vica_sim::vica_sim_agent_update>("/vica_sim/agent/update");
	cli_srv_vica_sim_agent_get = nh.serviceClient<vica_sim::vica_sim_agent_get>("/vica_sim/agent/get");
	cli_srv_vica_sim_agent_get_list = nh.serviceClient<vica_sim::vica_sim_agent_get_list>("/vica_sim/agent/get_list");

	//sim
	cli_srv_vica_sim_sim_get_target_pos = nh.serviceClient<vica_sim::vica_sim_sim_get_target_pos>("/vica_sim/sim/get_target_pos");
	cli_srv_vica_sim_sim_set_target_pos = nh.serviceClient<vica_sim::vica_sim_sim_set_target_pos>("/vica_sim/sim/set_target_pos");
	cli_srv_vica_sim_sim_get_robot_pos = nh.serviceClient<vica_sim::vica_sim_sim_get_robot_pos>("/vica_sim/sim/get_robot_pos");
	cli_srv_vica_sim_sim_start_sim = nh.serviceClient<vica_sim::vica_sim_sim_start_sim>("/vica_sim/sim/start_sim");
	cli_srv_vica_sim_sim_get_sim_result = nh.serviceClient<vica_sim::vica_sim_sim_get_sim_result>("/vica_sim/sim/get_sim_result");
	cli_srv_vica_sim_sim_reset_sim = nh.serviceClient<vica_sim::vica_sim_sim_reset_sim>("/vica_sim/sim/reset_sim");

}

com::~com() {
	// TODO Auto-generated destructor stub
}

bool com::call_env_init() {
	vica_sim::vica_sim_env_init msg;
}

void com::call_env_get_size() {
	vica_sim::vica_sim_env_get_size msg;
}

bool com::call_env_set_size(const int x, const int y) {
	vica_sim::vica_sim_env_set_size msg;
}

bool com::call_env_gui(const bool gui_on) {
	vica_sim::vica_sim_env_gui msg;

	msg.request.gui = true;

	if (cli_srv_vica_sim_env_gui.call(msg)) {
		ROS_INFO("Resultat GUI : %d", msg.response.res);
	} else {
		ROS_ERROR("Failed to call service GUI");
		return 1;
	}

}

bool com::call_env_stop() {
	vica_sim::vica_sim_env_stop msg;
}

bool com::call_agent_add() {
	vica_sim::vica_sim_agent_add msg;
}

bool com::call_agent_delete(int id) {
	vica_sim::vica_sim_agent_delete msg;
}

bool com::call_agent_update() {
	vica_sim::vica_sim_agent_update msg;
}

bool com::call_agent_get() {
	vica_sim::vica_sim_agent_get msg;
}

bool com::call_agent_get_list() {
	vica_sim::vica_sim_agent_get_list msg;
}

bool com::call_sim_get_target_pos() {
	vica_sim::vica_sim_sim_get_target_pos msg;
}

bool com::call_sim_set_target_pos() {
	vica_sim::vica_sim_sim_set_target_pos msg;
}

bool com::call_sim_get_robot_pos() {
	vica_sim::vica_sim_sim_get_robot_pos msg;
}

bool com::call_sim_start_sim() {
	vica_sim::vica_sim_sim_start_sim msg;
}

bool com::call_sim_get_sim_result() {
	vica_sim::vica_sim_sim_get_sim_result msg;
}

bool com::call_sim_reset_sim() {
	vica_sim::vica_sim_sim_reset_sim msg;
}

} /* namespace vica_eval */
