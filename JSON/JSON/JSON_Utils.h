#pragma once

#include "JSON_File.h"
#include "JSON_Object.h"
#include <map>
#include <any>


typedef std::map<std::string, std::any> NewList;
typedef std::list<std::string> file_content;
typedef std::pair<std::string, std::string> Splitted;

class JSON_Utils
{
	public:
		static JSON_Object*						decode(std::string& _file_name);
		static JSON_Object*						decode(std::filesystem::path& _file_path);
		static JSON_Object*						decode(std::list<std::string>& _content);

	private:
		// tools

		static JSON_Object*						decodeLine(std::string& line);
		static Splitted							split_key_value(std::string text, int position);
		static std::map<std::string, std::any>	prepareList(std::string& line);
		static bool								find_quote(std::string& line);
		static bool								find_brace(std::string& line);
		static bool								find_bracket(std::string& line);
		static bool								find_comma(std::string& line);
		static int								find_colon(std::string& line);
		static std::list<std::string>			splitArray(std::string text);
		static Splitted							split(std::string& text, int position);
		static void								clearWhiteSpaces(std::string& text);
		static void								prepareString(std::string& line);
		static void								print_m(const std::list<std::string>& container);
};

