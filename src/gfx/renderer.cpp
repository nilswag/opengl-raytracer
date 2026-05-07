#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.h"

QuadInstance::QuadInstance(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color)
	: m_color(color)
{
	m_model = glm::translate(m_model, glm::vec3(pos, 0.0f));
	m_model = glm::rotate(m_model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_model = glm::scale(m_model, glm::vec3(size, 1.0f));
}

Renderer::Renderer()
	: m_quadShader("shaders/quad/vertex.glsl", "shaders/quad/fragment.glsl", "Quad")
{
	static float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	static unsigned int indices[] = {
		
	};

	glCreateVertexArrays(1, &m_quadVao);

}

void Renderer::renderQuad(const QuadInstance& instance)
{
	m_quads.push_back(instance);
}

void Renderer::flush()
{

}