#pragma once
#include <string>
#include <vector>

namespace engine
{
	class Pipeline
	{
	public:
		Pipeline(const std::string& vertex_path, const std::string& fragment_path);

	private:
		static std::vector<char> read_file(const std::string& path);
	};
}