#include <fstream>
#include <stdexcept>
#include <print>

#include "pipeline.hpp"

namespace engine
{
	Pipeline::Pipeline(const std::string& vertex_path, const std::string& fragment_path)
	{
		auto vert_code = read_file(vertex_path);
		auto frag_code = read_file(fragment_path);

		std::println("Vert: {}\nFrag: {}", vert_code.size(), frag_code.size());
	}

	std::vector<char> Pipeline::read_file(const std::string& path)
	{
		std::ifstream file(path, std::ios::ate | std::ios::binary);
		if (!file.is_open())
			throw std::runtime_error("Failed to open file " + path);

		size_t size = static_cast<size_t>(file.tellg());
		std::vector<char> buf(size);

		file.seekg(0);
		file.read(buf.data(), size);
		file.close();

		return buf;
	}
}