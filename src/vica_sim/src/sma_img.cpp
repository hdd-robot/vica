/*
 * VICA
 * smaimg.cpp
 *  Created on: 13 mars 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#include "sma_img.h"

namespace vica_sim {

using namespace gagent;



SMA_Img::SMA_Img() {

}

SMA_Img::~SMA_Img() {
	AgentCore::syncAgentSystem();
	AgentCore::stopAgentSystem();

	//todo parcourir la liste des agents et appliquer un delete

}



bool SMA_Img::add_agent(int id, std::string type, std::string draw,
		std::string shape, int pos_x, int pos_y, int pos_z, std::string color,
		int size_x, int size_y, int size_z, std::string attr_list) {

	vica_agent_model* g ;
	if(type == "obstacle"){

	}

	if(type == "robot"){

	}

	if(type == "goal"){

	}

	g = new vica_agent_model();


	g->id = id;
	g->type = type;
	g->shape = shape;
	g->draw = draw;
	g->pos_x = pos_x;
	g->pos_y = pos_y;
	g->pos_z = pos_z;
	g->color = color;
	g->size_x = size_x;
	g->size_y = size_y;
	g->size_z = size_z;
	g->attr_list = attr_list;


	g->init();

	list_agents.push_back(g);
}

bool SMA_Img::update_agent() {

}

bool SMA_Img::delete_agent() {

}

bool SMA_Img::init_env() {
	AgentCore::initAgentSystem();
	AgentCore::initEnvironnementSystem(this->sma_env, true, 2000);
}

bool SMA_Img::stop_env() {

}
} /* namespace vica_sim */
