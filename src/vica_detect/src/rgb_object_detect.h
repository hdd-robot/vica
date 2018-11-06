/*
 * VICA
 * rgb_object_detect.h
 *  Created on: 4 nov. 2018
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#ifndef VICA_DETECT_SRC_RGB_OBJECT_DETECT_H_
#define VICA_DETECT_SRC_RGB_OBJECT_DETECT_H_

#include <std_msgs/String.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
//opencv
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
//tensorflow


namespace vica_detect {

class RGB_object_detect {
public:
	RGB_object_detect();
	virtual ~RGB_object_detect();
	void callback(const sensor_msgs::ImageConstPtr& input);
	void showWindow();
	void make_predection();



private:
	ros::Publisher pub;
	ros::Subscriber sub;
	ros::NodeHandle n;


	sensor_msgs::Image cam1;
	cv_bridge::CvImagePtr cv_ptr1;
	cv::Mat image1;
	cv_bridge::CvImagePtr stitching_output;


};

} /* namespace vica_detect */

#endif /* VICA_DETECT_SRC_RGB_OBJECT_DETECT_H_ */
