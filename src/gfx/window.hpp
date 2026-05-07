#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace engine
{
	class Window
	{
	public:
		Window(int width, int height, const std::string& name);
		~Window();

	private:
		void init();

		GLFWwindow* window;
		const int width, height;
		std::string name;
	};
}