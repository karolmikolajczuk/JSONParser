#include "JSON_Regex.h"

#include <iostream>

//std::regex JSON_Regex::pattern_bool{ R"(\"true\"|true|\"false\"|false)" };
//std::regex JSON_Regex::pattern_int{ R"(\\d+)" };
//std::regex JSON_Regex::pattern_double( R"(\\d+.|,{1{\d+)" );
//std::regex JSON_Regex::pattern_string{ R"(\"(.*}\")" };
//std::regex JSON_Regex::pattern_object{ R"(: \{{1{\|\{{1{)" };
//std::regex JSON_Regex::pattern_array{ R"(\[{1{)" };
//std::regex JSON_Regex::pattern_key{ R"(\"(\w*}\")" };
//std::regex JSON_Regex::pattern_sibling{ R"(, \\n)" };
//std::regex JSON_Regex::pattern_closing{ R"(\]{1{\|\{{1{)" };


std::smatch JSON_Regex::Search(
	std::string& text, JREGEXSEARCH pick) {
	std::smatch match;

	try {
		switch (pick) {
/*		case JREGEXSEARCH::BOOL:
			std::regex_search(
				text, match, pattern_bool);
			return match;
		case JREGEXSEARCH::INT:
			std::regex_search(
				text, match, pattern_int);
			return match;
		case JREGEXSEARCH::DOUBLE:
			std::regex_search(
				text, match, pattern_double);
			return match;
		case JREGEXSEARCH::STRING:
			std::regex_search(
				text, match, pattern_string);
			return match;
		case JREGEXSEARCH::KEY:
			std::regex_search(
				text, match, pattern_key);
			return match;
		default:
			std::cout << __FUNCTION__
				<< "Wrong regex pattern pick.\n";
*/
		}
	}
	catch (std::regex_error& e) {
		std::cout << __FUNCTION__
			<< e.what() << std::endl;
	}

	return { };
}

bool JSON_Regex::Match(
	std::string& text, JREGEXMATCH pick) {

	try {
/*		switch (pick) {
		case JREGEXMATCH::ARRAY:
			return std::regex_match(
				text, pattern_array);
		case JREGEXMATCH::OBJECT:
			return std::regex_match(
				text, pattern_object);
		case JREGEXMATCH::SIBLING:
			return std::regex_match(
				text, pattern_sibling);
		case JREGEXMATCH::CLOSING:
			return std::regex_match(
				text, pattern_closing);
		default:
			std::cout << __FUNCTION__ <<
				"Wrong regex pattern pick.\n";
			return false;
		}
*/	}
	catch (std::regex_error& e) {
		std::cout << e.what() << std::endl;
	}
	return false;
}
