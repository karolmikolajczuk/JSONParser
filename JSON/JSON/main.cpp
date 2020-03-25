#include "JSON_Utils.h"

int main() {


	/*
		open file *.json

		read whole file

		create JSON_Object	

		decode that file into JSON_Object

		->	read key - value

		->	save it at the beginning as string

		->	print everything

		->	later on save it as specific types
		
		->	->	key's are string's no matter what

		->	->	value's are very different
		
		->	->	->	bool, int, double, string, another object itself, list of all that values and object's aswell

	*/
	std::string s = "example.json";
	JSON_Object* json = JSON_Utils::decode(s);

	json->printData();
	// nie przechodzi przez wszystkie

	std::cout << std::endl;
	json->printResult(json->getValue("\"Acronym\""));
	std::cout << std::endl;

	return 1;
}