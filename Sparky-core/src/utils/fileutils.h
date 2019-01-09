#pragma once

#include <string>
#include <fstream>
#include <streambuf>
#include <cerrno>

#include <stdio.h>
#include <string.h>



namespace sparky {

	// C implementation
	std::string read_file(const char* filepath)
	{
		FILE* file;
		errno_t err = fopen_s(&file, filepath, "r"); 
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);

		char* data = new char[length + 1];
		memset(data, 0, length + 1);

		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete(data);
		return result;
	}

	// C++ implementation
	std::string read_file_cpp(const char *filepath)
	{
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
		}
		throw(errno);
	}
}
