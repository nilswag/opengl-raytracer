#include <string>
#include <glad/gl.h>
#include "shader.hpp"
#include "../util/io.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	program = glCreateProgram();
	GLuint vertexShader = compileShader(readFile(vertexPath), GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(readFile(fragmentPath), GL_FRAGMENT_SHADER);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

GLuint Shader::compileShader(const std::string& src, GLenum type)
{
	GLuint shader = glCreateShader(type);

	const char* GLchar = src.c_str();
	glShaderSource(shader, 1, &csrc, nullptr);
	glCompileShader(shader);

	return shader;
}