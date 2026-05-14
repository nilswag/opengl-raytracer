#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

inline std::string readFile(const std::string& path)
{
	std::ifstream f("resources/" + path);
	if (!f.is_open())
		throw std::runtime_error("Unable to open file: " + path);
	std::stringstream buf;
	buf << f.rdbuf();
	return buf.str();
}