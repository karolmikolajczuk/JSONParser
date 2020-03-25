#pragma once
#include <regex>

class JSON_Regex
{
	private:
		//static std::regex pattern_bool;
		//static std::regex pattern_int;
		//static std::regex pattern_double;
		//static std::regex pattern_string;
		//static std::regex pattern_object;
		//static std::regex pattern_array;
		//static std::regex pattern_key;
		//static std::regex pattern_sibling;
		//tatic std::regex pattern_closing;
		
	public:
	
		enum class JREGEXMATCH {
			OBJECT,
			ARRAY,
			SIBLING,
			CLOSING
		};

		enum class JREGEXSEARCH {
			BOOL,
			INT,
			DOUBLE,
			STRING,
			KEY
		};

		static std::smatch Search(std::string& text, JREGEXSEARCH pick);
		static bool Match(std::string& text, JREGEXMATCH pick);
};

