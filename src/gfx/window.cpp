#include <stdexcept>
#include <string>
#include <print>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "window.hpp"

static void APIENTRY glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::string severityStr = [severity]()
		{
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_LOW: return "Low";
			case GL_DEBUG_SEVERITY_MEDIUM: return "Medium";
			case GL_DEBUG_SEVERITY_HIGH: return "High";
			}
		}();

	std::string typeStr = [type]()
		{
			switch (type)
			{
			case GL_DEBUG_TYPE_ERROR: return "Error";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated behavior";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined behavior";
			case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
			case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
			case GL_DEBUG_TYPE_OTHER: return "Other";
			}
		}();

	std::println("OpenGL debug ({}): [{}:{}] {}", id, severityStr, typeStr, message);
}

static void glfwErrorCallback(int error, const char* description)
{
	std::println("GLFW error ({}): {}", error, description);
}

Window::Window(int width, int height, const std::string& title)
	: width(width), height(height)
{
	if (!glfwInit())
		throw std::runtime_error("Unable to initialize glfw");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!window)
		throw std::runtime_error("Unable to initialize glfw window");

	glfwMakeContextCurrent(window);

	if (!gladLoadGL(static_cast<GLADloadfunc>(glfwGetProcAddress)))
		throw std::runtime_error("Unable to initialize glad");
	
#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glErrorCallback, nullptr);
	GLuint unusedIds = 0;
	glDebugMessageControl(
		GL_DONT_CARE,
		GL_DONT_CARE,
		GL_DONT_CARE,
		0,
		nullptr,
		GL_TRUE
	);
#endif
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(window);
}

void Window::pollEvents() const
{
	glfwPollEvents();
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(window);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	this->width = width;
	this->height = height;
	glViewport(0, 0, width, height);
}