#include <string>
#include <vector>
#include <stdexcept>
#include <print>
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

static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
	vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
	vk::DebugUtilsMessageTypeFlagsEXT type,
	const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* puserData
)
{
	// TODO: actually divide logging severity into sections
	std::string typeStr;

	if (type & vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral)
		typeStr += "GENERAL ";

	if (type & vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation)
		typeStr += "VALIDATION ";

	if (type & vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance)
		typeStr += "PERFORMANCE ";

	if (typeStr.empty())
		typeStr = "N/A";

	std::println("validation layer: {} msg: {}", typeStr, pCallbackData->pMessage);

	return vk::False;
}


void App::createInstance()
{
	// vulkan application info
	vk::ApplicationInfo appInfo = { };
	appInfo.pApplicationName = title.c_str();
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = vk::ApiVersion14;

	// check if required glfw extensions for vulkan are available
	auto requiredExtensions = getRequiredInstanceExtentions();
	auto extensionProperties = context.enumerateInstanceExtensionProperties();
	auto unsupportedPropertyIt = std::ranges::find_if(requiredExtensions,
		[&extensionProperties](const auto& requiredExtension) {
			return std::ranges::none_of(extensionProperties, [requiredExtension](const auto& extensionProperty)
				{
					return strcmp(extensionProperty.extensionName, requiredExtension) == 0;
				});
		});
	if (unsupportedPropertyIt != requiredExtensions.end())
	{
		throw std::runtime_error("Required extension not supported: " + std::string(*unsupportedPropertyIt));
	}

	// vulkan instance info
	vk::InstanceCreateInfo createInfo = {};
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = validationLayers.size();
	createInfo.ppEnabledLayerNames = validationLayers.data();
	createInfo.enabledExtensionCount = requiredExtensions.size();
	createInfo.ppEnabledExtensionNames = requiredExtensions.data();

	instance = vk::raii::Instance(context, createInfo);
	
	// check if all specified validation layers are available
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

std::vector<const char*> App::getRequiredInstanceExtentions()
{
	unsigned int glfwExtensionCount = 0;
	auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef _DEBUG
	extensions.push_back(vk::EXTDebugUtilsExtensionName);
#endif

	return extensions;
}

App::App(int width, int height, const std::string& title)
	: width(width), height(height), title(title), instance(nullptr), debugMessenger(nullptr)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	createInstance();

#ifdef _DEBUG
	// setup debug callback
	vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
	);

	vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(
		vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
		vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
		vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
	);

	vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT = {};
	debugUtilsMessengerCreateInfoEXT.messageSeverity = severityFlags;
	debugUtilsMessengerCreateInfoEXT.messageType = messageTypeFlags;
	debugUtilsMessengerCreateInfoEXT.pfnUserCallback = &debugCallback;

	debugMessenger = instance.createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfoEXT);
#endif
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