#include <string>
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>

inline std::string read_file(const std::string& path)
{
	spdlog::trace("Reading file with path {}", path);
	std::string str;
	std::string line;

	std::ifstream f("resources/" + path);
	if (!f.is_open())
	{
		spdlog::error("Error while opening file ({})", path);
		return str;
	}

	while (std::getline(f, line))
		str += line + '\n';

	if (f.bad())
		spdlog::error("Error while reading file ({})", path);

	return str;
}