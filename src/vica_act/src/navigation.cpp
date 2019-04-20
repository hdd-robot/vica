/*
 * VICA
 * navigation.cpp
 *  Created on: 15 avr. 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#include "navigation.h"

namespace vica_act {

navigation::navigation() {


}

navigation::~navigation() {
	// TODO Auto-generated destructor stub
}


bool navigation::env_goto_pos(vica_act::vica_act_goto_pos::Request &req,
			                  vica_act::vica_act_goto_pos::Response &res) {

	geometry_msgs::Twist move;
	move.linear.x = 0.2; //speed value m/s
	move.angular.z = 0;
	movement_pub->publish(move);


	ROS_INFO("env_goto_pos");

	res.res = true;
	return true;
}

void navigation::get_odom_pose(const nav_msgs::Odometry::ConstPtr& msg){
	this->current_pose = *msg;
}


} /* namespace vica_act */
