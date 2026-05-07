#include <string>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "../util/io.h"

unsigned int Shader::compileShader(const std::string& src, GLenum type)
{
	unsigned int id = glCreateShader(type);
	const char* srcStr = static_cast<const GLchar*>(src.c_str());
	glShaderSource(id, 1, &srcStr, nullptr);
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
		spdlog::warn("Compiling shader with empty src ({}:{})", m_tag, tag);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::string log;
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		log.resize(length);

		glGetShaderInfoLog(id, log.size(), nullptr, log.data());
		
		spdlog::error("Unable to compile shader ({}:{}):\n{}", m_tag, tag, log);
		return id;
	}

	spdlog::trace("Compiled shader ({}:{})", m_tag, tag);
	return id;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& tag)
	: m_id(0), m_tag(tag)
{
	std::string vertexSrc = readFile(vertexPath);
	std::string fragmentSrc = readFile(fragmentPath);
	
	unsigned int vertexShader = compileShader(vertexSrc, GL_VERTEX_SHADER);
	unsigned int fragmentShader = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);
	
	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	int success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		int length;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
		std::string log;
		log.resize(length);

		glGetProgramInfoLog(m_id, log.size(), nullptr, log.data());

		spdlog::error("Unable to link shader program ({}):\n{}", m_id, log);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	if (!hasUniform(name)) return;
	glUniform2fv(m_uniforms.at(name), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	if (!hasUniform(name)) return;
	glUniform3fv(m_uniforms.at(name), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	if (!hasUniform(name)) return;
	glUniform4fv(m_uniforms.at(name), 1, glm::value_ptr(value));
}

void Shader::setMat2(const std::string& name, const glm::mat2& value) const
{
	if (!hasUniform(name)) return;
	glUniformMatrix2fv(m_uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat3(const std::string& name, const glm::mat3& value) const
{
	if (!hasUniform(name)) return;
	glUniformMatrix3fv(m_uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
	if (!hasUniform(name)) return;
	glUniformMatrix4fv(m_uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}