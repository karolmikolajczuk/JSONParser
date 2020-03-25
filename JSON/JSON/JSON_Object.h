#pragma once

#include "JSON.h"

#include <any>
#include <map>
#include <variant>

class JSON_Object;

typedef std::string KEY;	// each value as string
typedef std::any	VALUE;	// string, new object, list of values, list of new objects
typedef std::variant<std::monostate, std::string, JSON_Object*, std::list<std::string>, std::map<std::string, std::any>> RESULT;

enum class TYPE {
	INT,
	LIST,
	STRING,
	NEXT_OBJECT
};

class JSON_Object 
{
	public:
		// constructor
		JSON_Object();
		JSON_Object(KEY key, VALUE value);
		 
		// return value from map
		//template <typename T> T getValue(KEY key);
		RESULT getValue(KEY key);
		// insert data into map
		void putData(KEY key, VALUE value);

		// print all (including nested) 
		void printData();

		// print received result
		void printResult(RESULT result);

	private:

		// when parent has a lot of elements
		std::map<KEY, VALUE> key_values; // and it can be another element in it  
};

