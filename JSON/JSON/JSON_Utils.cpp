#include "JSON_Utils.h"

#define FLOW(text) std::cout << "[DEBUG]: " << text << " in function: \t" << __FUNCTION__ << '\t' << __LINE__ << '\n';


JSON_Object* JSON_Utils::decode(std::string& _file_name) {
	file_content content;
	try {
		content = JSON_File(_file_name).getFileContent();
	}
	catch (std::exception& e) {
		FLOW(e.what());
		return nullptr;
	}

	if (!content.size())
		return nullptr;

	std::string front_line = content.front();

	try {
		content.pop_front();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	// decide if there is : and we have to split it
	int colon_pos = JSON_Utils::find_colon(front_line);

	JSON_Object* main_object = new JSON_Object();

	// no colon, decide if what it is
	if (colon_pos == std::string::npos) {
		// then it's the end of current object
		FLOW("No colon");

		main_object->putData("", decode(content));
	}
	else {
		FLOW("Colon");

		Splitted key_value = split(front_line, colon_pos);

		clearWhiteSpaces(key_value.first);
		clearWhiteSpaces(key_value.second);

		FLOW(key_value.first);
		FLOW(key_value.second);

		if (find_quote(key_value.second)) {
			// it's just string
			main_object->putData(key_value.first, key_value.second);
		}
		else if (find_brace(key_value.second)) {
			// it's new object
			main_object->putData(key_value.first, decode(content));
		}
		else if (find_bracket(key_value.second)) {
			// it's list 
			main_object->putData(key_value.first, prepareList(key_value.second));
		}

		//if (content.size() == 0) 
	}

	// this is what user get's
	return main_object;
}

JSON_Object* JSON_Utils::decode(std::filesystem::path& _file_path) {
	file_content content = JSON_File(_file_path).getFileContent();
	// TODO

	return nullptr;
}

JSON_Object* JSON_Utils::decode(std::list<std::string>& _content) {

	if (!_content.size())
		return nullptr;

	std::string front_line = _content.front();

	try { _content.pop_front(); }
	catch (std::exception& e) { std::cout << e.what() << std::endl; }

	JSON_Object* object = new JSON_Object();

	while (front_line.rfind("\}") == std::string::npos) {
		std::cout << "BEGIN------------------------------------------------\n";

		// decide if there is : and we have to split it
		FLOW("Computing colon");
		int colon_pos = JSON_Utils::find_colon(front_line);

		// no colon, decide if what it is
		FLOW("Iterating while loop...");
		if (colon_pos == std::string::npos) {
			FLOW("No colon");
			if (front_line.find("\}\,") != std::string::npos ||
				front_line.find("\}") != std::string::npos) {

				front_line = _content.front();
				try { _content.pop_front(); }
				catch (std::exception& e) { std::cout << e.what() << std::endl; }

				return object;
			}
		}
		else {
			FLOW("Colon");
			std::cout << front_line << std::endl;
			std::cout << front_line.length() << std::endl;
			std::cout << colon_pos << std::endl;
			
			Splitted key_value = split(front_line, colon_pos);

			clearWhiteSpaces(key_value.first);
			clearWhiteSpaces(key_value.second);

			std::cout << key_value.first << " " << 
				key_value.second << std::endl;

			if (!(key_value.second.find("\{") == std::string::npos)) {
				// it's new object
				FLOW("Found brace");

				print_m(_content);

				object->putData(key_value.first, decode(_content));
				
				std::cout << "Just returned from nested object\n";

			}
			else if (!(key_value.second.find("\[") == std::string::npos)) {
				// it's list 
				FLOW("Found bracket");

				// check for colon inside because it's different for just values
				if (find_colon(key_value.second) == std::string::npos) {
					// just values
					object->putData(key_value.first, 
						splitArray(key_value.second));
				}
				else {
					// and for key-value pairs
					object->putData(key_value.first, 
						prepareList(key_value.second));
				}
			}
			else if (!(key_value.second.find("\"") == std::string::npos)) {
				// it's just string
				FLOW("Found quote in:");
				FLOW(key_value.second);
				object->putData(key_value.first, key_value.second);
			}
			front_line = _content.front();
			_content.pop_front();
		}
		std::cout << "END------------------------------------------------\n";
		if (_content.size() == 0) break;
	}

	FLOW("Returning object");
	return object;
}

NewList JSON_Utils::prepareList(std::string& line) {
	/*
	"key": ["a1": "aV", "a2": "aV", "a3": {asdsadsa}]
	where we get the right part only
	*/
	NewList result;

	// clear from brackets [ ] 
	line = line.substr(1, line.length() - 2);

	// split by comma ,
	std::list<std::string> selected_pairs = splitArray(line);

	// split each by semi-colon :
	std::list<Splitted> splitted_pairs;
	for (auto& pair : selected_pairs) {
		splitted_pairs.push_back(
			split_key_value(pair, find_colon(pair))
		);
	}
	// we are now key - value (unknown type)
	// 
	// if value is { 
	// then invoke decode for some kind of line

	// set key as key, set value as value
	for (Splitted& kv : splitted_pairs) {
		if (find_bracket(kv.second))
			result[kv.first] = prepareList(kv.second);
		else if (find_brace(kv.second))
			result[kv.first] = decodeLine(kv.second);
		else if (find_quote(kv.second))
			result[kv.first] = kv.second;
		else
			FLOW("some weird shit with this string: " + kv.second);
	}

	// return decoded/prepared string as NewList
	return result;
}

JSON_Object* JSON_Utils::decodeLine(std::string& line) {
	// here the line is a value which contains the whole new object
	/*
	.... : ["KEY": {"KEY": "VALUE"}]
	*/

	return nullptr;
}

Splitted JSON_Utils::split_key_value(std::string text, int position) {
	FLOW(text);
	return std::make_pair(std::string(std::begin(text), std::begin(text) + position),
		std::string(std::begin(text) + position, std::end(text)));
}

bool JSON_Utils::find_quote(std::string& line) {
	return line.find("\"") >= 0;
}

bool JSON_Utils::find_brace(std::string& line) {
	return line.find('{') >= 0;
}

bool JSON_Utils::find_bracket(std::string& line) {
	return line.find('[') >= 0;
}

bool JSON_Utils::find_comma(std::string& line) {
	return line.at(line.length() - 1) == ',';
}

int JSON_Utils::find_colon(std::string& line) {
	return line.find(':');
}

std::list<std::string> JSON_Utils::splitArray(std::string text) {
	// prepare string
	FLOW(text);

	text = text.erase(0, text.find_first_not_of("["));
	text = text.substr(0, text.find_last_not_of("]")+1);

	FLOW(text);

	// pattern for splitting
	const std::string comma = ",";

	// split whole line by comma and put it into 
	std::list<std::string> splitted_string;

	// splitting
	int last_searching = 0;
	int present_searching = -1;
		
	while (last_searching != std::string::npos) {
		std::cout << "Last searching = " << last_searching << " ----- " << __LINE__ << std::endl;
		std::cout << "Present searching = " << present_searching << " ----- " << __LINE__ << std::endl;

		present_searching = text.find(comma);
		std::cout << "Found at " << present_searching << " ----- " << __LINE__ << std::endl;

		if (present_searching == std::string::npos) {
			FLOW(text);
			splitted_string.push_back(text);
		}
		else {
			FLOW(text.substr(last_searching, present_searching));

			splitted_string.push_back(
				text.substr(last_searching, present_searching));

			text = text.substr(present_searching+1);
		}
		FLOW(text);
		last_searching = present_searching;
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	for (auto& content : splitted_string) {
		std::cout << content << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	return splitted_string;
}

std::pair<std::string, std::string> JSON_Utils::split(std::string& text, int position) {
	return std::make_pair(text.substr(0, position),
		text.substr(position + 1));
}

void JSON_Utils::clearWhiteSpaces(std::string& text) {
	text = text.erase(0, text.find_first_not_of("\t\v\n\r "));
	text = text.erase(text.find_last_not_of("\t\v\n\r ") + 1);
}

void JSON_Utils::prepareString(std::string& line) {
	FLOW(line);
	if (find_comma(line))
		line = line.substr(0, line.length() - 2);
	FLOW(line);
	if (find_quote(line))
		line = line.substr(1, line.length() - 2);
	FLOW(line);
}

void JSON_Utils::print_m(const std::list<std::string>& container) {
	std::cout << "------------------------------------\n";
	for (const auto& ref : container) { std::cout << ref << std::endl; }
	std::cout << "------------------------------------\n";
}