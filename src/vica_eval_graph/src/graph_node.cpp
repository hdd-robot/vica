#include <ros/ros.h>
#include <vica_msgs/path_angles.h>
#include <vica_msgs/path_angles_list.h>
#include <vica_msgs/vica_eval_graph_get_list_best_pos.h>

#include "graph.h"

vica_msgs::path_angles_list lst_path_tmp;
vica_msgs::path_angles_list lst_path;

vica_eval::path_graph pgraph;


void analyze_data_lidar(){
	lst_path = lst_path_tmp;

	ROS_INFO(" --- loop ---- ");


	for( auto pth : lst_path.lst_path ){
		pgraph.add_node(pth.min_teta,pth.max_teta,pth.min_dist,pth.max_dist);
		ROS_INFO(" --> count");
	}

	pgraph.draw_graph();
	pgraph.get_netx_pos();
	//pgraph.clear_grap();




}



void list_pat_cb(const vica_msgs::path_angles_listConstPtr& input) {
	lst_path_tmp = *input;
}




bool get_best_list_pos(vica_msgs::vica_eval_graph_get_list_best_pos::Request &req,
		vica_msgs::vica_eval_graph_get_list_best_pos::Response &res) {

	ROS_INFO("get_best_list_pos srv called");



	//res.res = true;
	return true;
}






int main(int argc, char **argv) {
	ros::init(argc, argv, "graph_node");
	ros::NodeHandle n;
	ros::Rate loop_rate(0.1);

	ros::ServiceServer graph_srv_1 = n.advertiseService("/vica_eval_graph/get_list_best_pos", get_best_list_pos);

	ros::Subscriber sub1 = n.subscribe("/vica_robot/sensor/laser/list_path", 1, list_pat_cb);




	pgraph.set_goal(0,10);
	pgraph.set_init_node();

	while (ros::ok()) {

		analyze_data_lidar();

		ros::spinOnce();
		loop_rate.sleep();
	}

}
