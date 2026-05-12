#include <string>
#include <vector>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include "app.hpp"

#ifdef _DEBUG
const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};
#else
const std::vector<const char*> validationLayers = { };
#endif

App::App(int width, int height, const std::string& title)
	: instance(nullptr)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	vk::ApplicationInfo appInfo = { };
	appInfo.pApplicationName = title.c_str();
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = vk::ApiVersion14;

	unsigned int glfwExtensionCount = 0;
	auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	auto extensionProperties = context.enumerateInstanceExtensionProperties();
	for (unsigned int i = 0; i < glfwExtensionCount; i++)
	{
		if (std::ranges::none_of(extensionProperties, [glfwExtension = glfwExtensions[i]](const auto& extensionProperty)
			{ return strcmp(extensionProperty.extensionName, glfwExtension) == 0; }))
		{
			throw std::runtime_error("Required GLFW extension is not supported: " + std::string(glfwExtensions[i]));
		}
	}

	vk::InstanceCreateInfo createInfo = {};
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	instance = vk::raii::Instance(context, createInfo);

	auto layerProperties = context.enumerateInstanceLayerProperties();
	auto unsupportedLayerIt = std::ranges::find_if(validationLayers,
		[&layerProperties](const auto& requiredLayer) {
			return std::ranges::none_of(layerProperties, [requiredLayer](const auto& layerProperty)
				{ return strcmp(layerProperty.layerName, requiredLayer) == 0; });
		});
	if (unsupportedLayerIt != validationLayers.end())
	{
		throw std::runtime_error("Required validation layer not supported: " + std::string(*unsupportedLayerIt));
	}
}

App::~App()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void App::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}