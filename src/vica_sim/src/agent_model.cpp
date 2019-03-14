/*
 * VICA
 * agent_model.cpp
 *  Created on: 13 mars 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#include "agent_model.h"

namespace vica_sim {

//using namespace gagent;

class myTickerBehaviour: public TickerBehaviour {
public:
	myTickerBehaviour(Agent* ag) :
			TickerBehaviour(ag, 1000) {
	}

	void onTick() {
		//std::cout << " tictac " << std::endl << std::flush;
		this_agent->setAttribut("x", std::to_string(i++));
		this_agent->setAttribut("y", std::to_string(i++));
		this_agent->attributUpdated();
	}
private:
	int i = 120;
};

vica_agent_model::~vica_agent_model() {

}

vica_agent_model::vica_agent_model():gagent::Agent() {
	;
}

void vica_agent_model::setup() {
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

	this_agent->setAttribut("id", "agent3");
	this_agent->setAttribut("name", "agent3");
	this_agent->setAttribut("color", "yellow");
	this_agent->setAttribut("shape", "circle");
	this_agent->setAttribut("pattern", "diag3");
	this_agent->setAttribut("size_x", "20");
	this_agent->setAttribut("size_y", "30");
	this_agent->setAttribut("size_z", "10");

	this_agent->attributUpdated();
	myTickerBehaviour* b4 = new myTickerBehaviour(this);
	addBehaviour(b4);

}

} /* namespace vica_sim */
