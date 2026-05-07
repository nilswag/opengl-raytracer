#pragma once
#include <string>
#include <glad/glad.h>
#include <map>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

class shader
{
public:
	shader(const std::string& vertex_path, const std::string& fragment_path, const std::string& tag);
	~shader();

	inline GLuint getId() const { return id; }

	void set_vec2(const std::string& name, const glm::vec2& value) const;
	void set_vec3(const std::string& name, const glm::vec3& value) const;
	void set_vec4(const std::string& name, const glm::vec4& value) const;

	void set_mat2(const std::string& name, const glm::mat2& value) const;
	void set_mat3(const std::string& name, const glm::mat3& value) const;
	void set_mat4(const std::string& name, const glm::mat4& value) const;

private:
	std::map<std::string, GLint> uniforms;
	std::string tag;
	GLuint id;

	GLuint compile_shader(const std::string& src, GLenum type);

	inline bool has_uniform(const std::string& name) const
	{
		if (uniforms.contains(name)) return true;
		spdlog::error("Uniform does not exist: {}", name);
		return false;
	}
};