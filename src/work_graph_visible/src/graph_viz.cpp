#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <sensor_msgs/PointCloud2.h>

// PCL
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>



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
Mat image3;

sensor_msgs::PointCloud2 pointCloud2;

image_transport::Publisher image_pub_;


void cam1_cb(const sensor_msgs::ImageConstPtr& input) {
	cam1 = *input;
//	ROS_INFO("Input from cam1");
	try {
		cv_ptr1 = cv_bridge::toCvCopy(input,input->encoding);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
}

void cam2_cb(const sensor_msgs::ImageConstPtr& input) {
	cam2 = *input;
//	ROS_INFO("Input from cam2");
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

void detect_Object() {

	Mat image_tmp(480, 640, CV_8UC3, cv::Scalar(255, 255, 255));

	int width = pointCloud2.width;
	int height = pointCloud2.height;

	// Convert from u (column / width), v (row/height) to position in array
	// where X,Y,Z data starts
	float minX = 0;
	float minY = 0;
	float minZ = 0;

	float maxX = 0;
	float maxY = 0;
	float maxZ = 0;

	int matrix[height][width];
	int v,u;

	for(v=0; v< height; v++) {
		for(u=0; u < width; u++) {
			matrix[v][u]=0;
		}
	}
	unsigned int tmpx,tmpy;

	for(v=0; v< height; v++) {
		for(u=0; u < width; u++) {

			int arrayPosition = v * pointCloud2.row_step + u * pointCloud2.point_step;

			// compute position in array where x,y,z data start
			int arrayPosX = arrayPosition + pointCloud2.fields[0].offset;// X has an offset of 0
			int arrayPosY = arrayPosition + pointCloud2.fields[1].offset;// Y has an offset of 4
			int arrayPosZ = arrayPosition + pointCloud2.fields[2].offset;// Z has an offset of 8
			float X = 0.0;
			float Y = 0.0;
			float Z = 0.0;
			memcpy(&X, &pointCloud2.data[arrayPosX], sizeof(float));
			memcpy(&Y, &pointCloud2.data[arrayPosY], sizeof(float));
			memcpy(&Z, &pointCloud2.data[arrayPosZ], sizeof(float));

			if(minX > X ) {minX = X;}
			if(minY > Y ) {minY = Y;}
			if(minZ > Z ) {minZ = Z;}

			if(maxX < X ) {maxX = X;}
			if(maxY < Y ) {maxY = Y;}
			if(maxZ < Z ) {maxZ = Z;}

			if(std::isnan(X)){continue;}
			if(std::isnan(Y)){continue;}
			if(std::isnan(Z)){continue;}



			X = X + 3;
			if (X >= 5){
				X=5;
			}

			tmpy = (int)(((Z*640.0)/5.0));
			tmpx = (int)(((X*480.0)/5.0));

		//	std::cout << "Z="<< Z << " X="<< X << " : " << tmpx << "," << tmpy <<"," << std::endl;

			matrix[tmpx][tmpy] += 1 ;



			//std::cout << "(x,y,z) (R) = " << X << ","<< Y << ","<< Z << ", ( " << R << ",,)" << std::endl;
		}
	}

	std::cout << "min(x,y,z) = (" << minX << ","<< minY << ","<< minZ << ")" << std::endl;
	std::cout << "max(x,y,z) = (" << maxX << ","<< maxY << ","<< maxZ << ")" << std::endl;


	int color;
	for(v=0; v< height; v++) {
		for(u=0; u < width; u++) {
			color = matrix[v][u];
			if(color < 10){
				cv::circle(image_tmp, cv::Point(v, u), 1, CV_RGB(255, 255, 255));
				continue;
			}

			cv::circle(image_tmp, cv::Point(v, u), 1, CV_RGB(0, 0, 0));
		}
	}


//	pcl::PointCloud< pcl::PointXYZ > PointCloudXYZ;




//	pcl::fromROSMsg(pointCloud2,PointCloudXYZ);
//	std::cout << "width is " << PointCloudXYZ.width << std::endl;
//	std::cout << "height is " << PointCloudXYZ.height << std::endl;



	//int cloudsize = (PointCloudXYZ.width) * (PointCloudXYZ.height);
	/*
	std::cout << " --- BEGIN IMAGE --- "<< std::endl;
	for (int i=0; i< cloudsize; i++){
		std::cout << "(x,y,z) = " << PointCloudXYZ.points[i] << std::endl;
	}
	std::cout << " --- END OF IMAGE --- "<< std::endl;
	*/
//	for (int i=0; i< cloudsize; i++){
//
//	}


	/*
	cv::GlCamera camera;
	camera.lookAt(cv::Point3d(-10,-10,-10), cv::Point3d(0,0,2), cv::Point3d(0,1,0));
	cv::pointCloudShow(OPENCV_WINDOW_4, camera, PointCloudXYZ);
	*/


	image3 = image_tmp;

}

int main(int argc, char **argv) {

	ros::init(argc, argv, "image_converter");

	ros::NodeHandle n;


	ros::Publisher image_pub = n.advertise<sensor_msgs::Image>("/image_converter/output_video", 1);

	ros::Rate loop_rate(5);

	ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 1, cam1_cb);
	ros::Subscriber sub2 = n.subscribe("/camera/depth/image_raw", 1, cam2_cb);
	ros::Subscriber sub3 = n.subscribe("/camera/depth/points", 1, cam2_pointCloud);

	cv::namedWindow(OPENCV_WINDOW_1);
	cv::namedWindow(OPENCV_WINDOW_2);
	cv::namedWindow(OPENCV_WINDOW_3);


  int count = 0;
  while (ros::ok())
  {
    if ( cv_ptr1 && cv_ptr2 )
    {

       image1 = cv_ptr1->image;
       image2 = cv_ptr2->image;

       detect_Object();

       cv::imshow(OPENCV_WINDOW_1, image1);
       cv::imshow(OPENCV_WINDOW_2, image2);
       cv::imshow(OPENCV_WINDOW_3, image3);

       cv::waitKey(3);

       stitching_output = cv_ptr1;
       image_pub.publish(stitching_output);


       cv_ptr1.reset();
       cv_ptr2.reset();
    }

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

}
