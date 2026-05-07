#pragma once
#include <string>
#include <GLFW/glfw3.h>

class window
{
public:
	window(int width, int height, const std::string& title);
	~window();

	inline void swap_buffers()
	{
		glfwSwapBuffers(handle);
	}

	inline void poll_events()
	{
		glfwPollEvents();
	}

	inline int get_width() const
	{
		return width;
	}

	inline int get_height() const
	{
		return height;
	}

	inline bool should_close() const
	{
		return glfwWindowShouldClose(handle);
	}

private:
	static void frame_buffer_size_callback(GLFWwindow* handle, int width, int height);

	int width, height;
	GLFWwindow* handle;
};