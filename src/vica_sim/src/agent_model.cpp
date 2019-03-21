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
	myTickerBehaviour(Agent* ag) : TickerBehaviour(ag, 1000) {}

	void onTick() {
//		std::cout << " tictac " << std::endl << std::flush;
//		this_agent->setAttribut("x", "0");
//		this_agent->setAttribut("y", "4");
		this_agent->attributUpdated();
	}
private:
	int i = 120;
};

vica_agent_model::~vica_agent_model() {

}

vica_agent_model::vica_agent_model():gagent::Agent() {

}

void vica_sim::vica_agent_model::setup() {

	this_agent->addAttribut("id");
	this_agent->addAttribut("posx");
	this_agent->addAttribut("posy");
	this_agent->addAttribut("name");
	this_agent->addAttribut("color");
	this_agent->addAttribut("shape");
	this_agent->addAttribut("pattern");
	this_agent->addAttribut("sizex");
	this_agent->addAttribut("sizey");
	this_agent->addAttribut("sizez");


	this_agent->setAttribut("id", 		std::to_string(id));
	this_agent->setAttribut("posx", 	std::to_string(pos_x));
	this_agent->setAttribut("posy", 	std::to_string(pos_y));
	this_agent->setAttribut("name", 	"agent" + std::to_string(id));
	this_agent->setAttribut("color", 	color);
	this_agent->setAttribut("shape", 	shape);
	this_agent->setAttribut("pattern", 	"diag3");
	this_agent->setAttribut("sizex", 	std::to_string(size_x));
	this_agent->setAttribut("sizey", 	std::to_string(size_y));
	this_agent->setAttribut("sizez", 	std::to_string(size_z));

	this_agent->attributUpdated();

	myTickerBehaviour* b4 = new myTickerBehaviour(this);
	addBehaviour(b4);

}

} /* namespace vica_sim */

