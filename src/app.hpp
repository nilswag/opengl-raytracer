#pragma once
#include "gfx/window.hpp"

namespace engine
{
	class App
	{
	public:
		App();
		void run();

		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 800;
	private:
		Window window;
	};
}