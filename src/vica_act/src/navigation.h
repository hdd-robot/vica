/*
 * VICA
 * navigation.h
 *  Created on: 15 avr. 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#include "ros/ros.h"
#include <tf/transform_datatypes.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <vica_act/vica_act_goto_pos.h>



#ifndef VICA_ACT_SRC_NAVIGATION_H_
#define VICA_ACT_SRC_NAVIGATION_H_

namespace vica_act {

class navigation {
public:


	float distance_tolerance = 0.1;

	nav_msgs::Odometry current_pose;

	ros::NodeHandle *n;
	ros::Publisher *movement_pub;

	navigation();
	virtual ~navigation();

	bool env_goto_pos(vica_act::vica_act_goto_pos::Request &req, vica_act::vica_act_goto_pos::Response &res);

	void get_odom_pose(const nav_msgs::Odometry::ConstPtr& msg);

	float linear_velocity(geometry_msgs::Pose , float );

	float angular_velocity(geometry_msgs::Pose , float );

	float steering_angle(geometry_msgs::Pose goal_pose);

	float euclidean_distance(geometry_msgs::Pose goal_pose);



};

} /* namespace vica_act */

#endif /* VICA_ACT_SRC_NAVIGATION_H_ */






