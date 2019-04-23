#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <vector>
#include <list>
#include <std_msgs/String.h>
#include <work_graph_visible/path_angles.h>
#include <work_graph_visible/list_path.h>

#define inf 100

class Angle{
public:
	int   id;
	float teta_min;
	float teta_max;
	float teta_dist_min;
	float teta_dist_max;
	std::vector<float> values;

	bool operator<(const Angle& ang){
	     return (this->teta_min < ang.teta_min);
	}
};


bool pComp(Angle* a, Angle* b) { return *a < *b; }

sensor_msgs::LaserScan laser_data;

void laser_cb(const sensor_msgs::LaserScanConstPtr& input) {
	laser_data = *input;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "laser_detect_object");
	ros::NodeHandle n;
	ros::Subscriber sub1 = n.subscribe("/vica_robot/sensor/laser/scan", 1, laser_cb);
	ros::Publisher  pub1 = n.advertise<work_graph_visible::list_path>("/vica_robot/sensor/laser/objects", 1);

	ros::Rate loop_rate(5);
	std::list<Angle*> lst_angles_objects;
	std::list<Angle*> lst_angles_paths;

	std::vector<float> val_scan;

	while (ros::ok()) {
		int count = 0;
		int   const MAX_VAL 	 = 100 ;
		int   const SIMPLE	 	 = 720 ;
		float const MAX_INTERVAL = 0.1 ;

		if(laser_data.ranges.size() == 0){
			ros::spinOnce();
			loop_rate.sleep();
			continue;
		}

		val_scan.clear();

		for (int i=0; i<laser_data.ranges.size(); i++)
			val_scan.push_back(laser_data.ranges[i]);


		for(auto &val: val_scan){
			if (std::isinf(val)){
				val = MAX_VAL;
			}
		}

		std::vector<float>::iterator it_min ;
		std::vector<float>::iterator it_beg ;
		std::vector<float>::iterator it_end ;
		std::vector<float>::iterator it_l   ;
		std::vector<float>::iterator it_r   ;
		std::vector<float>::iterator it     ;

		for(auto lst : lst_angles_objects){
			delete lst;
		}
		lst_angles_objects.clear();
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
			}

			while(true){
				it_r ++ ;
				if(it_r == it_end){ break; }
				if(abs((*it_r)-(*(it_r-1))) >= MAX_INTERVAL ){ break; }
			}
			++count;
			Angle* a = new Angle;
			a->id = count;
			a->teta_dist_min = *(it_l+1);
			a->teta_min = ((2 * M_PI)/SIMPLE) * ( (it_l+1) - it_beg) ;
			a->teta_dist_max = *(it_r-1);
			a->teta_max = ((2 * M_PI)/SIMPLE) * ( (it_r-1) - it_beg) ;


			//std::copy(it_l+1,it_r,a->values.begin());

			lst_angles_objects.push_back(a);


			while(it_l != it_r){
				*it_l = MAX_VAL;
				it_l++;
			}
			it_min = std::min_element(it_beg,it_end);
		}


		lst_angles_objects.sort(pComp);

		Angle* fst = lst_angles_objects.front();
		Angle* lst = lst_angles_objects.back();
		if (fst->id != lst->id){
			if((fst->teta_min < 0.3 )&&(lst->teta_max >6.2)){
				lst->teta_max 		= fst->teta_max;
				lst->teta_dist_max 	= fst->teta_dist_max;
				lst_angles_objects.erase(lst_angles_objects.begin());
				delete fst;
			}
		}


		for(auto lst : lst_angles_paths){
			delete lst;
		}
		lst_angles_paths.clear();

		std::list<Angle*>::iterator lst_angles_objects_it     = lst_angles_objects.begin();
		std::list<Angle*>::iterator lst_angles_objects_it_beg = lst_angles_objects.begin();
		std::list<Angle*>::iterator lst_angles_objects_it_end = lst_angles_objects.end();
		while (lst_angles_objects_it != lst_angles_objects_it_end){
			Angle* a = new Angle;
			a->teta_min 	 = (*lst_angles_objects_it)->teta_max;
			a->teta_dist_min = (*lst_angles_objects_it)->teta_dist_max;
			if(lst_angles_objects_it == (std::prev(lst_angles_objects_it_end,1))){
				a->teta_max 	 = (*lst_angles_objects_it_beg)->teta_min;
				a->teta_dist_max = (*lst_angles_objects_it_beg)->teta_dist_min;
			}
			else{
				a->teta_max 	 = (*std::next(lst_angles_objects_it,1))->teta_min;
				a->teta_dist_max = (*std::next(lst_angles_objects_it,1))->teta_dist_min;
			}
			lst_angles_paths.push_back(a);
			lst_angles_objects_it ++;
		}

//		std::cout << " -- Data -- " << std::endl;
//		for(auto lst : lst_angles_objects){
//			std::cout << " ---- " << std::endl;
//			std::cout << "teta_dist_min : " << lst->teta_dist_min << std::endl;
//			std::cout << "teta_min      : " << lst->teta_min << std::endl;
//			std::cout << "teta_dist_max : " << lst->teta_dist_max << std::endl;
//			std::cout << "teta_max      : " << lst->teta_max << std::endl;
//		}
//		std::cout << " -- END Data -- " << std::endl << std::endl << std::endl;


		work_graph_visible::list_path msg_lst_ang;
		work_graph_visible::path_angles* path_agl;



		for(auto lst : lst_angles_paths){
			path_agl = new work_graph_visible::path_angles();

			path_agl->min_teta = lst->teta_min;
			path_agl->min_dist = lst->teta_dist_min;
			path_agl->max_teta = lst->teta_max;
			path_agl->max_dist = lst->teta_dist_max;

			msg_lst_ang.lst_path.push_back(*path_agl);
			delete path_agl;
		}
		pub1.publish(msg_lst_ang);

//		std::cout << " -- Data Reverse-- " << std::endl;
//		for(auto lst : lst_angles_paths){
//			std::cout << " ---- " << std::endl;
//			std::cout << "teta_dist_min : " << lst->teta_dist_min << std::endl;
//			std::cout << "teta_min      : " << lst->teta_min << std::endl;
//			std::cout << "teta_dist_max : " << lst->teta_dist_max << std::endl;
//			std::cout << "teta_max      : " << lst->teta_max << std::endl;
//		}
//		std::cout << " -- END Data Reverse -- " << std::endl << std::endl << std::endl;

		ros::spinOnce();
		loop_rate.sleep();
	}



}


