#pragma once
#include <string>
#include <glad/gl.h>

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	inline void use() const { glUseProgram(program); }
	inline GLuint getPrograM() const { return program; }

private:
	GLuint compileShader(const std::string& src, GLenum type);

	GLuint program;
};