#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <sensor_msgs/PointCloud2.h>
#include <sstream>
#include <string>
// PCL
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

#include <pcl/io/pcd_io.h>

#include "gazebo_cube_spawner.h"

static const std::string OPENCV_WINDOW_1 = "RGB";
static const std::string OPENCV_WINDOW_2 = "DEPTH";
static const std::string OPENCV_WINDOW_3 = "CREATED";

static const std::string OPENCV_WINDOW_4 = "3D";

using namespace cv;

sensor_msgs::Image cam1;
sensor_msgs::Image cam2;

sensor_msgs::Image output;
cv_bridge::CvImagePtr cv_ptr1;          //ROS and OpenCV suitable image for cam1
cv_bridge::CvImagePtr cv_ptr2;          //ROS and OpenCV suitable image for cam2
cv_bridge::CvImagePtr cv_ptr3;          //ROS and OpenCV suitable image for cam2
cv_bridge::CvImagePtr stitching_output; //ROS and OpenCV suitable output
Mat image1;
Mat image2;


sensor_msgs::PointCloud2 pointCloud2;

image_transport::Publisher image_pub_;


void cam1_cb(const sensor_msgs::ImageConstPtr& input) {
	cam1 = *input;
	try {
		cv_ptr1 = cv_bridge::toCvCopy(input,input->encoding);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
}

void cam2_cb(const sensor_msgs::ImageConstPtr& input) {
	cam2 = *input;
	try {
		cv_ptr2 = cv_bridge::toCvCopy(input,input->encoding);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
}

void cam2_pointCloud(const sensor_msgs::PointCloud2ConstPtr& cloud_msg) {
	pointCloud2 = *cloud_msg;
}


int main(int argc, char **argv) {

	ros::init(argc, argv, "get_screenshot");

	ros::NodeHandle n;

	 gazebo_test_tools::GazeboCubeSpawner spawner(n);

	//ros::Publisher image_pub = n.advertise<sensor_msgs::Image>("/image_converter/output_video", 1);


	// 5 sec
	ros::Rate loop_rate(0.5);

	// 1 sec
	ros::Rate wait_stable_object(0.4);

	ros::Subscriber sub1 = n.subscribe("/vica_robot/sensor/kinect/rgb/image_raw", 1, cam1_cb);
	//ros::Subscriber sub2 = n.subscribe("/vica_robot/sensor/kinect/depth/image_raw", 1, cam2_cb);
	//ros::Subscriber sub3 = n.subscribe("/vica_robot/sensor/kinect/depth/points", 1, cam2_pointCloud);

	cv::namedWindow(OPENCV_WINDOW_1);
	//cv::namedWindow(OPENCV_WINDOW_2);


  int count = 0;
  while (ros::ok()){
    if ( cv_ptr1 ){

    	//ROS_INFO_STREAM("delete model");
		system("rosservice call  /gazebo/delete_model \"model_name: 'obj_name_1'\"");

		std::string name = "obj_name_1";
		float x = 1;
		float y = 0;
		float z = 0.4;
		std::string frame_id = "world";

		float dim = 0.1;
		float mass = 0.1;
		//ROS_INFO_STREAM("spown new model model");
		spawner.spawnRandcylinder(name, frame_id, x, y, z);

		wait_stable_object.sleep();

		image1 = cv_ptr1->image;
		//image2 = cv_ptr2->image;

		//ROS_INFO_STREAM("show Image");
		cv::imshow(OPENCV_WINDOW_1, image1);
		//cv::imshow(OPENCV_WINDOW_2, image2);

		std::stringstream ss;
		ss << "/home/ros/workspace_vica/src/work_gen_img/img/cylinder/rgb/img_" << count << ".jpg";
		imwrite(ss.str(), image1);

//		ss.str("");
//		ss << "/home/ros/workspace_vica/src/work_gen_img/img/cylinder/depth/img_"
//				<< count << ".jpg";
//		imwrite(ss.str(), image2);
//
//		ss.str("");
//		ss << "/home/ros/workspace_vica/src/work_gen_img/img/cylinder/pcl/img_"
//				<< count << ".pcd";
//		pcl::io::savePCDFile(ss.str(), pointCloud2);

		ROS_INFO_STREAM("models saved");

		cv::waitKey(3);
		stitching_output = cv_ptr1;
		cv_ptr1.reset();
		//cv_ptr2.reset();


		}

    ros::spinOnce();

    ROS_INFO_STREAM("----pause---");
    loop_rate.sleep();

    ++count;
  }

}
