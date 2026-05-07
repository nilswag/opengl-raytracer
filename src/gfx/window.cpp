#include "window.hpp"

namespace engine
{
	Window::Window(int width, int height, const std::string& name)
		: width(width), height(height), name(name)
	{
		init();
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		
		window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	}
}