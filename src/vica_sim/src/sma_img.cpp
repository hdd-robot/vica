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
}



bool SMA_Img::add_agent() {
	vica_agent_model* g = new vica_agent_model();
	g->init();
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
