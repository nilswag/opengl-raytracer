#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "shader.h"

struct quad_instance
{
	quad_instance(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color);

	glm::mat4 model;
	glm::vec4 color;
};

class renderer
{
public:	
	renderer();
	void render_quad(const quad_instance& instance);
	void flush();

private:
	std::vector<quad_instance> quads;
	Shader quad_shader;
	GLuint quad_vao;
};