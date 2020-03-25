#pragma once

// #include <any>
#include <list>
#include <string>


class JSON
{
	public:
		// constructor's
		JSON(std::string& key, std::string& value);
		JSON(std::string& key, std::list<std::string>& values);
		
		// destructor
		~JSON();

		// setter's
		void setValue(std::string& value);
		void setValues(std::list<std::string>& values);
		void setValues(std::string& value);
		void setKey(std::string& key);

		// getter's
		std::string getKey();
		std::string getValue();
		std::list<std::string> getValues();

	private:
		
		/*"Acronym": "SGML",*/

		// key of element
		std::string key;
		// value of element
		std::string value;

		/*"GlossSeeAlso": ["GML", "XML"]*/

		// array of straight values
		std::list<std::string> values;
};

