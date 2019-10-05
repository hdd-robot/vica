/*
 * VICA
 * rgb_object_detect.cpp
 *  Created on: 4 nov. 2018
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#include "rgb_object_detect.h"

namespace vica_detect {



RGB_object_detect::RGB_object_detect() {
	sub = n.subscribe("/vica_robot/sensor/kinect/rgb/image_raw", 10, &RGB_object_detect::callback, this);
	pub = n.advertise<sensor_msgs::Image>("/vica_detect/kinect/rgb/output_video", 1);
	cv::namedWindow("RGB");
}

RGB_object_detect::~RGB_object_detect() {

}

void RGB_object_detect::callback(const sensor_msgs::ImageConstPtr& input) {
	cam1 = *input;
	try {
		cv_ptr1 = cv_bridge::toCvCopy(input,input->encoding);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
}

void RGB_object_detect::showWindow(){
	ros::Rate loop_rate(5);
	while (ros::ok()){
	    if ( cv_ptr1  ){
	       image1 = cv_ptr1->image;
	       cv::imshow("RGB", image1);
	       cv::waitKey(3);
	       stitching_output = cv_ptr1;
	       this->pub.publish(stitching_output);
	       cv_ptr1.reset();
	    }
	    ros::spinOnce();
	    loop_rate.sleep();
	}
}

void RGB_object_detect::make_predection(){
	ros::Rate loop_rate(5);
		while (ros::ok()){
		    if ( cv_ptr1  ){
		       image1 = cv_ptr1->image;
		       cv::imshow("RGB", image1);
		       cv::waitKey(3);
		       stitching_output = cv_ptr1;
		       this->pub.publish(stitching_output);
		       cv_ptr1.reset();
		    }
		    ros::spinOnce();
		    loop_rate.sleep();
		}

}


} /* namespace vica_detect */

int main(int argc, char **argv) {
	ros::init(argc, argv, "vica_detect_rgb_detect");
	vica_detect::RGB_object_detect listener;
	listener.make_predection();
	ros::spin();
	return 0;
}







