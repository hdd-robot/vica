/*
 * VICA
 * environment_model.cpp
 *  Created on: 13 mars 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#include "environment_model.h"

namespace vica_sim {


void SMA_Env::init_env() {


}

void SMA_Env::link_attribut() {

	this->link_id   ("id");
	this->link_name ("name");
	this->link_pos_x("posx");
	this->link_pos_y("posy");
	this->link_color("color");
	this->link_size ("size");
	this->link_size_x("sizex");
	this->link_size_y("sizey");
	this->link_size_z("sizez");
	this->link_shape("shape");
}

void SMA_Env::event_loop() {

}


} /* namespace vica_sim */
