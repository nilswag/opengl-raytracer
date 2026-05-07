#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

static void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
	auto const src_str = [source]() 
	{
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
		default: return "UNKNOWN";
		}
	}();

	auto const type_str = [type]() 
		{
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
		default: return "UNKNOWN";
		}
	}();

	spdlog::level::level_enum spd_level = [severity]() 
		{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_MEDIUM: return spdlog::level::level_enum::warn;
		case GL_DEBUG_SEVERITY_HIGH: return spdlog::level::level_enum::err;
		default: return spdlog::level::level_enum::debug;
		}
	}();

	spdlog::log(spd_level, "GL Log: [{}:{}] {}", src_str, type_str, message);
}

void window::frame_buffer_size_callback(GLFWwindow* handle, int width, int height)
{
	window* ptr = static_cast<window*>(glfwGetWindowUserPointer(handle));
	ptr->width = width;
	ptr->height = height;
	glViewport(0, 0, width, height);

	spdlog::debug("Window resized ({}x{})", width, height);
}

window::window(int width, int height, const std::string& title)
	: width(width), height(height), handle(nullptr)
{
	if (!glfwInit())
	{
		spdlog::critical("Failed to initialize glfw");
		std::abort();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!handle)
	{
		spdlog::critical("Failed to initialize glfw window");
		std::abort();
	}

	glfwMakeContextCurrent(handle);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		spdlog::critical("Failed to initialize glad");
		std::abort();
	}

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(message_callback, nullptr);

	glViewport(0, 0, width, height);
	glfwSetWindowUserPointer(handle, this);
	glfwSetFramebufferSizeCallback(handle, frame_buffer_size_callback);

	spdlog::info("Vendor: {}", (char*)glGetString(GL_VENDOR));
	spdlog::info("Renderer: {}", (char*)glGetString(GL_RENDERER));
	spdlog::info("Version: {}", (char*)glGetString(GL_VERSION));

	spdlog::debug("Window initialized ({}x{})", width, height);
}

window::~window()
{
	glfwDestroyWindow(handle);
	glfwTerminate();
	spdlog::debug("Window deinitialized");
}