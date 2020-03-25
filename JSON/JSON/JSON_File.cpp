#include "JSON_File.h"

#include <string>

JSON_File::JSON_File(std::string& _file_name) :
	file_name{ _file_name },
	file_path{ _file_name } {
	if (this->isFileOK()) {
		try {
			std::cout << "File opening..\n";
			this->file.open(file_path.string(),
				std::ios::in | std::ios::out);
			std::cout << "File opened..\n";
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}

JSON_File::JSON_File(fs::path& _file_path) :
	file_name{ _file_path.filename().string() },
	file_path{ _file_path } {
	if (this->isFileOK()) {
		try {
			this->file.open(file_path.string(),
				std::ios::in | std::ios::out);
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}

JSON_File::~JSON_File() {
	this->file.close();
	this->file_name.clear();
	this->file_path.clear();
}

void JSON_File::setFilePath(std::string& _file_path) {
	this->file_name = _file_path;
	this->file_path = _file_path;
}

void JSON_File::setFilePath(fs::path _file_path) {
	this->file_path = _file_path;
	this->file_name = _file_path.filename().string();
}

std::list<std::string> JSON_File::getFileContent() {
	std::cout << __FUNCTION__ << std::endl;

	// check file
	if (!this->isFileOK()) throw std::exception("Cant read file");
	std::cout << "File opened..\n";

	// content holder
	std::list<std::string> file_content;
	std::cout << "Creating list of strings..\n";

	// get whole data from file
	while (!this->file.eof()) {
		std::string line_from_file;
		getline(file, line_from_file);
		std::cout << line_from_file << std::endl;

		file_content.push_back(line_from_file);
	}

	return file_content;
}

std::string JSON_File::getFileName() {
	return this->file_name;
}

std::string JSON_File::getFilePath() {
	return this->file_path.string();
}

bool JSON_File::isFileOK() {
	return this->doesFileExists() && this->isFileEmpty();
}

bool JSON_File::doesFileExists() {
	return std::filesystem::file_size(this->file_path);
}

bool JSON_File::isFileEmpty() {
	return std::filesystem::exists(file_path);
}