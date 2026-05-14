#include <glad/gl.h>
#include "gfx/window.hpp"

int main()
{
	Window window(800, 800, "OpenGL");

	while (!window.shouldClose())
	{
		window.pollEvents();

		float color[3] = { 0.0f };
		glClearNamedFramebufferfv(0, GL_COLOR, 0, color);
		window.swapBuffers();
	}

	return 0;
}