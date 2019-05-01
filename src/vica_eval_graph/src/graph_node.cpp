#include <ros/ros.h>
#include <vica_msgs/path_angles.h>
#include <vica_msgs/path_angles_list.h>
#include "graph.h"

vica_msgs::path_angles_list lst_path_tmp;
vica_msgs::path_angles_list lst_path;



void list_pat_cb(const vica_msgs::path_angles_listConstPtr& input) {
	lst_path_tmp = *input;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "graph_node");
	ros::NodeHandle n;
	ros::Rate loop_rate(0.1);

	ros::Subscriber sub1 = n.subscribe("/vica_robot/sensor/laser/list_path", 1, list_pat_cb);


	vica_eval::path_graph pgraph;

	pgraph.set_goal(0,10);

	pgraph.set_init_node();

	while (ros::ok()) {
		lst_path = lst_path_tmp;

		ROS_INFO(" --- loop ---- ");

		for( auto pth : lst_path.lst_path ){
			pgraph.add_node(pth.min_teta,pth.max_teta,pth.min_dist,pth.max_dist);
			ROS_INFO(" --> count");
		}

		pgraph.draw_graph();

		//pgraph.clear_grap();


		ros::spinOnce();
		loop_rate.sleep();
	}

}
