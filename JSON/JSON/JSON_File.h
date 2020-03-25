#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

class JSON_File
{
	
	public:

		// CONSTRUCTORS

		JSON_File(std::string& _file_name);
		JSON_File(fs::path& _file_path);

		// DESTRUCTOR

		~JSON_File();

		// METHODS

		void setFilePath(std::string& _file_path);
		void setFilePath(fs::path _file_path);
	
		std::list<std::string> getFileContent();

		std::string getFileName();
		std::string getFilePath();

	private:

		// METHODS

		bool isFileOK();
		bool doesFileExists();
		bool isFileEmpty();


		// POLES

		std::fstream file;

		std::string file_name;
		fs::path file_path;

};

