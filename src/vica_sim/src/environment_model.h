/*
 * VICA
 * environement_model.h
 *  Created on: 13 mars 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#include <Agent.hpp>
#include <Behaviour.hpp>
#include <AgentCore.hpp>
#include <Environnement.hpp>


#ifndef VICA_SIM_SRC_ENVIRONEMENT_MODEL__H_
#define VICA_SIM_SRC_ENVIRONEMENT_MODEL__H_

namespace vica_sim {


//using namespace gagent;

class SMA_Env : public gagent::Environnement {

public:
	virtual void init_env();

	virtual void link_attribut();

	virtual void event_loop();
};



} /* namespace vica_sim */

#endif /* VICA_SIM_SRC_ENVIRONEMENT_MODEL__H_ */
