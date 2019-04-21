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

}


bool navigation::env_goto_pos(vica_act::vica_act_goto_pos::Request &req,
			                  vica_act::vica_act_goto_pos::Response &res) {

	ros::Rate r(20);
	geometry_msgs::Twist move;

	while (euclidean_distance(req.pose) >= distance_tolerance){

		move.linear.x  = linear_velocity(req.pose, 0.10);
		move.linear.y  = 0;
		move.linear.z  = 0;

		move.angular.x = 0;
		move.angular.y = 0;
		move.angular.z = angular_velocity(req.pose, 1.0);

		movement_pub->publish(move);

		ros::spinOnce();
		r.sleep();
	}



	move.linear.x  = 0;
	move.linear.y  = 0;
	move.linear.z  = 0;

	move.angular.x = 0;
	move.angular.y = 0;
	move.angular.z = 0;

	movement_pub->publish(move);

	ROS_INFO("position OK");

	res.res = true;
	return true;
}

void navigation::get_odom_pose(const nav_msgs::Odometry::ConstPtr& msg){
	this->current_pose = *msg;
}

float navigation::linear_velocity(geometry_msgs::Pose goal_pose, float constant ) {
	float equ_dist = euclidean_distance(goal_pose);
	float vel = constant * equ_dist;
	return vel;
}

float navigation::steering_angle(geometry_msgs::Pose goal_pose) {
	float ang = 0;
	ang = atan2((goal_pose.position.y - current_pose.pose.pose.position.y),
			    (goal_pose.position.x - current_pose.pose.pose.position.x) );
	return ang;
}

float navigation::angular_velocity(geometry_msgs::Pose goal_pose, float constant) {
	float ang_vel;
	tf::Pose pose;
	tf::poseMsgToTF(current_pose.pose.pose, pose);
	double yaw_angle = tf::getYaw(pose.getRotation());

	ang_vel =  constant * (steering_angle(goal_pose) - yaw_angle);



	ROS_INFO("yaw_angle : %f , ang_vel : %f ", yaw_angle, ang_vel );
	return ang_vel;
}

float navigation::euclidean_distance(geometry_msgs::Pose goal_pose) {

	ROS_INFO("POSE  ( %f , %f )  ", current_pose.pose.pose.position.x , current_pose.pose.pose.position.y);

	float equ_dist = sqrt(pow(goal_pose.position.x - current_pose.pose.pose.position.x,2) +
			              pow(goal_pose.position.y - current_pose.pose.pose.position.y,2)   );
	return equ_dist;
}

} /* namespace vica_act */





















