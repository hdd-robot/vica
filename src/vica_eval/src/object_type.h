/*
 * VICA
 * object_type.h
 *  Created on: 17 mars 2019
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */
#include <string>
#include <queue>
#include <vector>
#include <boost/regex.hpp>
#include <fstream>


#ifndef VICA_EVAL_SRC_OBJECT_TYPE_H_
#define VICA_EVAL_SRC_OBJECT_TYPE_H_

namespace vica_eval {

class object_type {
public:
	object_type();
	virtual ~object_type();

	static void load_csv_file(const std::string file_name);

	static void insert_object(const std::vector<std::string> obj);

	static std::queue<std::vector<std::string>> list_object;

	bool load_next_object();


//private:
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
};


} /* namespace vica_eval */

#endif /* VICA_EVAL_SRC_OBJECT_TYPE_H_ */
