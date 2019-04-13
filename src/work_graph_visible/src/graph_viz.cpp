#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>


#include <vector>
#include <list>

#define inf 100

class Angle{
public:
	float teta_min;
	float teta_max;

	float teta_dist_min;
	float teta_dist_max;

	std::vector<float> values;
};


sensor_msgs::LaserScan laser_data;

void laser_cb(const sensor_msgs::LaserScanConstPtr& input) {

	laser_data = *input;
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "laser_detect_object");

	ros::NodeHandle n;

	ros::Subscriber sub1 = n.subscribe("/vica_robot/sensor/laser/scan", 1, laser_cb);

	ros::Rate loop_rate(0.5);


	std::list<Angle*> lst_angles;

	int count = 0;

	while (ros::ok()) {

		int   const MAX_VAL 	 = 100 ;
		int   const SIMPLE	 	 = 720 ;
		float const MAX_INTERVAL = 0.1 ;

		std::vector<float> val_scan(laser_data.ranges.size());
		val_scan.swap(laser_data.ranges);


		if(val_scan.size() == 0){
			ros::spinOnce();
			loop_rate.sleep();
			++count;
			continue;
		}

		for(auto &val: val_scan){
			if (std::isinf(val)){
				val = MAX_VAL;
			}
		}


		std::vector<float>::iterator it_min;
		std::vector<float>::iterator it_beg;
		std::vector<float>::iterator it_end;
		std::vector<float>::iterator it_l  ;
		std::vector<float>::iterator it_r  ;
		std::vector<float>::iterator it    ;
		lst_angles.clear();

		it_beg = val_scan.begin();
		it_end = val_scan.end();


		it_min = std::min_element(it_beg,it_end);

		while( (*it_min) < MAX_VAL){
			it_l = it_min;
			it_r = it_min;

			while(true){
				it_l -- ;
				if(it_l == it_beg){ break; }
				if(abs((*it_l)-(*(it_l+1))) >= MAX_INTERVAL ){ break; }
				//std::cout << (*it_l) << " " ;
			}

			while(true){
				it_r ++ ;
				if(it_r == it_end){ break; }
				if(abs((*it_r)-(*(it_r-1))) >= MAX_INTERVAL ){ break; }
				//std::cout << (*it_r) << " " ;
			}

			Angle* a = new Angle;
			a->teta_dist_min = *(it_l+1);
			a->teta_min = ((2 * M_PI)/SIMPLE) * ( (it_l+1) - it_beg) ;
			a->teta_dist_max = *(it_r-1);
			a->teta_max = ((2 * M_PI)/SIMPLE) * ( (it_r-1) - it_beg) ;

			//std::copy(it_l+1,it_r,a->values.begin());

			lst_angles.push_back(a);


			while(it_l < it_r){
				*it_l = MAX_VAL;
				it_l++;
			}
			it_min = std::min_element(it_beg,it_end);
		}



		for(auto lst : lst_angles){
			std::cout << " -- Data -- " << std::endl;
			std::cout << "teta_dist_min : " << lst->teta_dist_min << std::endl;
			std::cout << "teta_min      : " << lst->teta_min << std::endl;
			std::cout << "teta_dist_max : " << lst->teta_dist_max << std::endl;
			std::cout << "teta_max      : " << lst->teta_max << std::endl;

		}



		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}



}
