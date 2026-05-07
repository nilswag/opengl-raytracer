#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "shader.h"

struct QuadInstance
{
	QuadInstance(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color);

	glm::mat4 m_model;
	glm::vec4 m_color;
};

class Renderer
{
public:	
	Renderer();
	void renderQuad(const QuadInstance& instance);
	void flush();

private:
	std::vector<QuadInstance> m_quads;
	Shader m_quadShader;
	unsigned int m_quadVao;
};