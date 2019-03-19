/*
 * VICA
 * object_type.cpp
 *  Created on: 17 mars 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */


#include "object_type.h"
#include <iostream>

namespace vica_eval {


std::queue<std::vector<std::string>> object_type::list_object;


object_type::object_type() {



}

object_type::~object_type() {
	// TODO Auto-generated destructor stub
}

void object_type::load_csv_file(const std::string file_name) {
	const boost::regex fieldsregx(",(?=(?:[^\"]*\"[^\"]*\")*(?![^\"]*\"))");
	std::ifstream infile;
	infile.open(file_name);
	std::string line;
	while (getline(infile, line)) {

		boost::sregex_token_iterator ti(line.begin(), line.end(), fieldsregx, -1);
		boost::sregex_token_iterator end2;
		std::vector<std::string> row;
		while (ti != end2) {
			std::string token = ti->str();
			++ti;
			row.push_back(token);
		}
		object_type::insert_object(row);
	}
	infile.close();
}

void object_type::insert_object(const std::vector<std::string> obj) {
	object_type::list_object.push(obj);
}

bool object_type::load_next_object() {
	if(!object_type::list_object.empty()){
		std::vector<std::string>  tmp_row;
		tmp_row = object_type::list_object.front();

		std::vector<std::string>::iterator it = tmp_row.begin();

		if (it != tmp_row.end()){this->id 	  = std::stoi(*it) ; it++;	}
		if (it != tmp_row.end()){this->type   = *it ; it++;				}
		if (it != tmp_row.end()){this->draw   = *it ; it++;				}
		if (it != tmp_row.end()){this->shape  = *it ; it++;				}
		if (it != tmp_row.end()){this->pos_x  = std::stoi(*it) ; it++;	}
		if (it != tmp_row.end()){this->pos_y  = std::stoi(*it) ; it++;	}
		if (it != tmp_row.end()){this->pos_z  = std::stoi(*it) ; it++;	}
		if (it != tmp_row.end()){this->color  = *it ; it++;				}
		if (it != tmp_row.end()){this->size_x = std::stoi(*it) ; it++;	}
		if (it != tmp_row.end()){this->size_y = std::stoi(*it) ; it++;	}
		if (it != tmp_row.end()){this->size_z = std::stoi(*it) ; it++;	}

		object_type::list_object.pop();

		return true;
	}
	return false;
}

} /* namespace vica_eval */





