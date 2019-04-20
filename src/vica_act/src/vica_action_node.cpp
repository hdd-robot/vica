
#include "ros/ros.h"

#include "navigation.h"





using namespace vica_act;

int main (int argc, char* argv[]){

	ros::init(argc, argv, "vica_act");
	ros::NodeHandle n;

	navigation nav;
	nav.n = &n;

	ros::ServiceServer env_srv_1 = n.advertiseService("/vica_act/nav/goto_pos", &navigation::env_goto_pos, &nav);

	ros::Subscriber currentPos = n.subscribe<nav_msgs::Odometry>("/vica_robot_controller/odom", 10, &navigation::get_odom_pose, &nav);

	ros::Publisher movement_pub = n.advertise<geometry_msgs::Twist>("/vica_robot_controller/cmd_vel",1);

	nav.movement_pub = &movement_pub;

	ros::spin();
	return 0;
}
