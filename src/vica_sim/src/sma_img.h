/*
 * VICA
 * smaimg.h
 *  Created on: 13 mars 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */


// include gAgent headers
#include <AgentCore.hpp>
#include <Environnement.hpp>
#include <Agent.hpp>
#include <Behaviour.hpp>

#include "agent_model.h"
#include "environment_model.h"


#ifndef VICA_SIM_SRC_SMAIMG_H_
#define VICA_SIM_SRC_SMAIMG_H_

namespace vica_sim {

class SMA_Img {
public:
	SMA_Img();

	virtual ~SMA_Img();

	bool add_agent();
	bool update_agent();
	bool delete_agent();

	bool init_env();

	bool stop_env();

private:

	SMA_Env sma_env;


};





} /* namespace vica_sim */

#endif /* VICA_SIM_SRC_SMAIMG_H_ */
