#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.h"

quad_instance::quad_instance(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color)
	: color(color)
{
	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));
}

renderer::renderer()
	: quad_shader("shaders/quad/vertex.glsl", "shaders/quad/fragment.glsl", "Quad")
{
	static float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	static unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	glCreateVertexArrays(1, &quad_vao);

	GLuint quad_vbo, quad_ebo;

	glCreateBuffers(1, &quad_vbo);
	glNamedBufferStorage(quad_vbo, sizeof(vertices), vertices, GL_MAP_READ_BIT);

}

void renderer::render_quad(const quad_instance& instance)
{
	quads.push_back(instance);
}

void renderer::flush()
{

}