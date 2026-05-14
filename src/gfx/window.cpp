#include <stdexcept>
#include <string>
#include <print>
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "window.hpp"

static void glfwErrorCallback(int error, const char* description)
{
	std::println(std::cerr, "GLFW error ({}): {}", error, description);
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