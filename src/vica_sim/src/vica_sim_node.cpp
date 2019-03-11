#include "ros/ros.h"

#include "vica_sim/vica_sim_env_init.h"
#include "vica_sim/vica_sim_env_get_size.h"
#include "vica_sim/vica_sim_env_set_size.h"
#include "vica_sim/vica_sim_env_gui.h"

// include gAgent headers
#include <AgentCore.hpp>
#include <Environnement.hpp>
#include <Agent.hpp>
#include <Behaviour.hpp>



using namespace gagent;

class myEnv : public gagent::Environnement {

public:
	virtual void init_env(){
		std::cout << " ------ Init Environnement ------ " << std::endl;
	};

	virtual void link_attribut(){
		this->link_id   ("id");
		this->link_name ("name");
		this->link_pos_x("x");
		this->link_pos_y("y");
		this->link_color("color");
		this->link_size ("size");
		this->link_size_x("size_x");
		this->link_size_y("size_y");
		this->link_size_z("size_z");
		this->link_shape("shape");
	};

	virtual void event_loop(){

		//std::cout<< "refresh -- " << std::endl;
	};
};



class myTickerBehaviour: public TickerBehaviour {
public:
	myTickerBehaviour(Agent* ag) : TickerBehaviour(ag,1000) { }

	void onTick(){
		//std::cout << " tictac " << std::endl << std::flush;

		this_agent->setAttribut("x",std::to_string(i++));
		this_agent->setAttribut("y",std::to_string(i++));
		this_agent->attributUpdated();
	}
private:
	int i =120 ;
};



class myAgent: public Agent {
public:
	myAgent() :
			Agent() {
	};

	void setup() {
		this_agent->addAttribut("id");
		this_agent->addAttribut("x");
		this_agent->addAttribut("y");
		this_agent->addAttribut("name");
		this_agent->addAttribut("color");
		this_agent->addAttribut("shape");
		this_agent->addAttribut("pattern");
		this_agent->addAttribut("size_x");
		this_agent->addAttribut("size_y");
	    this_agent->addAttribut("size_z");


		this_agent->setAttribut("id","agent3");
		this_agent->setAttribut("name","agent3");
		this_agent->setAttribut("color","yellow");
		this_agent->setAttribut("shape","circle");
		this_agent->setAttribut("pattern","diag3");
		this_agent->setAttribut("size_x","20");
		this_agent->setAttribut("size_y","30");
		this_agent->setAttribut("size_z","10");


		this_agent->attributUpdated();
		myTickerBehaviour* b4 = new myTickerBehaviour(this);
		addBehaviour(b4);
	}
};



bool srv_init(vica_sim::vica_sim_env_init::Request &req,
			  vica_sim::vica_sim_env_init::Response &res) {
//  ROS_INFO("request: action=%s, param=%s", req.action, req.param);
//  ROS_INFO("sending back response: [%d]", 1 );
//  res.res = 50;
	ROS_INFO("srv_init");

	myAgent* g = new myAgent();
	g->init();


	return true;
}

bool srv_get_size(vica_sim::vica_sim_env_get_size::Request &req,
				  vica_sim::vica_sim_env_get_size::Response &res) {

	ROS_INFO("srv_get_size");
	return true;
}

bool srv_set_size(vica_sim::vica_sim_env_set_size::Request &req,
				  vica_sim::vica_sim_env_set_size::Response &res) {

	ROS_INFO("srv_set_size");
	return true;
}

bool srv_gui(vica_sim::vica_sim_env_gui::Request &req,
			 vica_sim::vica_sim_env_gui::Response &res) {

	ROS_INFO("srv_gui");
	return true;
}

int main(int argc, char **argv) {

	myEnv e;
	AgentCore::initAgentSystem();
	AgentCore::initEnvironnementSystem(e, true, 2000);

	ros::init(argc, argv, "vica_sim");
	ros::NodeHandle n;

	//ENV
	ros::ServiceServer env_srv_1 = n.advertiseService("/vica_sim/env/init"	  , srv_init);
	ros::ServiceServer env_srv_2 = n.advertiseService("/vica_sim/env/get_size", srv_get_size);
	ros::ServiceServer env_srv_3 = n.advertiseService("/vica_sim/env/set_size",	srv_set_size);
	ros::ServiceServer env_srv_4 = n.advertiseService("/vica_sim/env/gui"     ,	srv_gui);

	ROS_INFO("Ready to add two ints.");


	ros::spin();


	ROS_INFO("Fin spin.");

	AgentCore::syncAgentSystem();
	AgentCore::stopAgentSystem();
	return 0;
}
