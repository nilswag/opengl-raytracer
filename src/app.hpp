#pragma once
#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_raii.hpp>

class App
{
public:
	App(int width, int height, const std::string& title);
	~App();

	App() = delete;
	App(const App&) = delete;
	App& operator=(const App&) = delete;

	void run();

private:
	void createInstance();
	std::vector<const char*> getRequiredInstanceExtentions();

	GLFWwindow* window;
	vk::raii::Context context;
	vk::raii::Instance instance;

	std::string title;
	int width, height;
};