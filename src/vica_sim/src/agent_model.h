/*
 * VICA
 * agent_model.h
 *  Created on: 13 mars 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#include <Agent.hpp>
#include <Behaviour.hpp>
#include <AgentCore.hpp>
#include <Environnement.hpp>
#include <string>
#include <sstream>

#ifndef VICA_SIM_SRC_AGENT_MODEL_H_
#define VICA_SIM_SRC_AGENT_MODEL_H_

namespace vica_sim {

using namespace gagent;

class vica_agent_model: public gagent::Agent {
public:
	vica_agent_model();
	virtual ~vica_agent_model();
	virtual void setup();

	int id;
	std::string type;
	std::string draw;
	std::string shape;
	int pos_x;
	int pos_y;
	int pos_z;
	std::string color;
	int size_x;
	int size_y;
	int size_z;
	std::string attr_list;
};

} /* namespace vica_sim */

#endif /* VICA_SIM_SRC_AGENT_MODEL_H_ */
