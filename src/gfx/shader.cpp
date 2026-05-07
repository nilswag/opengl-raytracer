#include <string>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "../util/io.h"

GLuint shader::compile_shader (const std::string& src, GLenum type)
{
	GLuint id = glCreateShader(type);
	const GLchar* src_str = static_cast<const GLchar*>(src.c_str());
	glShaderSource(id, 1, &src_str, nullptr);
	glCompileShader(id);

	std::string tag = "N/A";
	switch (type)
	{
	case GL_VERTEX_SHADER:
		tag = "Vertex";
		break;
	case GL_FRAGMENT_SHADER:
		tag = "Fragment";
		break;
	}

	if (src == "")
		spdlog::warn("Compiling shader with empty src ({}:{})", tag, tag);

	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::string log;
		GLint length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		log.resize(length);

		glGetShaderInfoLog(id, log.size(), nullptr, log.data());
		
		spdlog::error("Unable to compile shader ({}:{}):\n{}", tag, tag, log);
		return id;
	}

	spdlog::trace("Compiled shader ({}:{})", tag, tag);
	return id;
}

shader::shader(const std::string& vertex_path, const std::string& fragment_path, const std::string& tag)
	: id(0), tag(tag)
{
	std::string vertex_src = readFile(vertex_path);
	std::string fragment_src = readFile(fragment_path);
	
	GLuint vertex_shader = compile_shader(vertex_src, GL_VERTEX_SHADER);
	GLuint fragment_shader = compile_shader(fragment_src, GL_FRAGMENT_SHADER);
	
	id = glCreateProgram();
	glAttachShader(id, vertex_shader);
	glAttachShader(id, fragment_shader);
	glLinkProgram(id);

	GLint success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLint length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
		std::string log;
		log.resize(length);

		glGetProgramInfoLog(id, log.size(), nullptr, log.data());

		spdlog::error("Unable to link shader program ({}):\n{}", id, log);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

shader::~shader()
{
	glDeleteProgram(id);
}

void shader::set_vec2(const std::string& name, const glm::vec2& value) const
{
	if (!has_uniform(name)) return;
	glUniform2fv(uniforms.at(name), 1, glm::value_ptr(value));
}

void shader::set_vec3(const std::string& name, const glm::vec3& value) const
{
	if (!has_uniform(name)) return;
	glUniform3fv(uniforms.at(name), 1, glm::value_ptr(value));
}

void shader::set_vec4(const std::string& name, const glm::vec4& value) const
{
	if (!has_uniform(name)) return;
	glUniform4fv(uniforms.at(name), 1, glm::value_ptr(value));
}

void shader::set_mat2(const std::string& name, const glm::mat2& value) const
{
	if (!has_uniform(name)) return;
	glUniformMatrix2fv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}

void shader::set_mat3(const std::string& name, const glm::mat3& value) const
{
	if (!has_uniform(name)) return;
	glUniformMatrix3fv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}

void shader::set_mat4(const std::string& name, const glm::mat4& value) const
{
	if (!has_uniform(name)) return;
	glUniformMatrix4fv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}