#include <stdexcept>
#include <iostream>
#include <print>

#include "app.hpp"

namespace engine
{
	App::App()
		: window(WIDTH, HEIGHT, "Vulkan Window")
	{ }

	void App::run()
	{
		while (!window.should_close())
		{
			window.poll_events();
		}
	}
}

int main()
{
	engine::App app;

	try
	{
		app.run();
	} catch (const std::exception& e)
	{
		std::println(std::cerr, "Error: {}", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}