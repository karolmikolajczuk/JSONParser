#include "JSON_Object.h"

#include <iostream>
#define FLOW(text) std::cout << __FUNCTION__ << text << std::endl;

JSON_Object::JSON_Object() : key_values{ } {

}

JSON_Object::JSON_Object(KEY key, VALUE value) : key_values{ } {
	this->key_values[key] = value;
}

RESULT JSON_Object::getValue(KEY key) {
	std::cout << "Looking for: " << key << std::endl;
	// dla kazdej pary z mapy
	for (const auto& pair : this->key_values) {
		// sprawdz klucz, czy to jest taki sam
		std::cout << "Printing key: " << pair.first << std::endl;
		if (pair.first == key) {
			if (pair.second.type() == typeid(std::string)) {
				std::cout << "Returning this value: " << 
					std::any_cast<std::string>(pair.second);
				return std::any_cast<std::string>(pair.second);
			}
			else if (pair.second.type() == typeid(JSON_Object*)) {
				std::cout << "Returning this value: " << __LINE__;
				return std::any_cast<JSON_Object*>(pair.second);
			}
			else if (pair.second.type() == typeid(std::list<std::string>)) {
				std::cout << "Returning this value: " << __LINE__;
				return std::any_cast<std::list<std::string>>(pair.second);
			}
			else if (pair.second.type() == typeid(std::map<std::string, std::any>)) {
				std::cout << "Returning this value: " << __LINE__;
				return std::any_cast<std::map<std::string, std::any>>(pair.second);
			}
		} 
		else if (pair.second.type() == typeid(JSON_Object*)) {
			std::any returned = std::any_cast<JSON_Object*>(pair.second)->getValue(key);

			if (returned.type() == typeid(std::string)) {
				std::cout << "Returning this value: " <<
					std::any_cast<std::string>(returned);
				return std::any_cast<std::string>(returned);
			}
			else if (returned.type() == typeid(JSON_Object*)) {
				std::cout << "Returning this value: " << __LINE__;
				return std::any_cast<JSON_Object*>(returned);
			}
			else if (returned.type() == typeid(std::list<std::string>)) {
				std::cout << "Returning this value: " << __LINE__;
				return std::any_cast<std::list<std::string>>(returned);
			}
			else if (returned.type() == typeid(std::map<std::string, std::any>)) {
				std::cout << "Returning this value: " << __LINE__;
				return std::any_cast<std::map<std::string, std::any>>(returned);
			}
		}
	}
	
	std::cout << "Returning this value: " << __LINE__;
	return { };
}



void JSON_Object::putData(KEY key, VALUE value) {
	try {
		this->key_values[key] = value;
	}
	catch (std::exception& exc) {
		FLOW(exc.what());
	}
}

static int tabs = 0;

void JSON_Object::printData() {
	
	for (auto& key_value : this->key_values) {

		//FLOW(key_value.second.type().name());
		for (int i = 0; i < tabs; ++i) std::cout << '\t';
		std::cout << key_value.first << " : ";
		if (key_value.second.type() == typeid(std::string)) {
			std::cout << std::any_cast<std::string>(key_value.second) << std::endl;
		}
		else if (key_value.second.type() == typeid(JSON_Object*)) {
			++tabs;
			std::cout << "{\n";
			std::any_cast<JSON_Object*>(key_value.second)->printData();
		}
		else if (key_value.second.type() == typeid(std::list<std::string>)) {
			std::cout << "[ ";
			for (auto val : std::any_cast<std::list<std::string>>(key_value.second)) {
				std::cout << val << " ";
			}
			std::cout << "]\n";
		}
		else if (key_value.second.type() == typeid(std::map<std::string, std::string>)) {
			std::cout << "[\n";
			for (auto val : std::any_cast<std::map<std::string, std::string>>(key_value.second)) {
				std::cout << val.first << ": " << val.second << std::endl;
			}
			std::cout << "]\n";
		}
		else if (key_value.second.type() == typeid(std::map<std::string, std::any>)) {
			std::cout << "[\n";
			for (auto pair_map : std::any_cast<std::map<std::string, std::any>>(key_value.second)) {
				std::cout << pair_map.first << ": ";
				if (pair_map.second.type() == typeid(std::string)) {
					std::cout << std::any_cast<std::string>(pair_map.second) << std::endl;
				}
				else if (pair_map.second.type() == typeid(JSON_Object*)) {
					std::cout << "{\n";
					std::any_cast<JSON_Object*>(pair_map.second)->printData();
				}
				else if (pair_map.second.type() == typeid(std::list<std::string>)) {
					std::cout << "[ ";
					for (auto val : std::any_cast<std::list<std::string>>(pair_map.second)) {
						std::cout << val << " ";
					}
					std::cout << "]\n";
				}
				else if (pair_map.second.type() == typeid(std::map<std::string, std::string>)) {
					std::cout << "[\n";
					for (auto val : std::any_cast<std::map<std::string, std::string>>(key_value.second)) {
						std::cout << val.first << ": " << val.second << std::endl;
					}
					std::cout << "]\n";
				}
			}
			std::cout << "]\n";
		}
	}
	--tabs;
}

void JSON_Object::printResult(RESULT result) {
	std::string toPrint = "";
	toPrint = std::get<std::string>(result);
	std::cout << "Value: " << toPrint << std::endl;
}