//
// Created by hartmut on 2020/05/05.
//
#include "vkShmup/Vk/Instance.h"
#include "vkShmup/Vk/PhysicalDevice.h"
#include "vkShmup/Vk/Surface.h"
#include <iostream>
#include <set>

namespace vkShmup {

    const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };

    std::shared_ptr<Instance> Instance::create(const char* name) {
        return std::shared_ptr<Instance>{new Instance(name)};
    }

    Instance::Instance(const char* name) {
        createInstance(name);
#ifndef NDEBUG
        setupDebugMessenger();
#endif
    }

    Instance::~Instance() {
#ifndef NDEBUG
        destroyDebugUtilsMessengerEXT(nullptr);
#endif
        vkDestroyInstance(instance, nullptr);
    }

    bool Instance::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        std::set<std::string> requiredLayers(validationLayers.begin(), validationLayers.end());

        for (const auto& layerProperties : availableLayers) {
            requiredLayers.erase(layerProperties.layerName);
        }

        return requiredLayers.empty();
    }

    VkResult Instance::createDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, &debugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void Instance::createInstance(const char* name) {
#ifndef NDEBUG
        if (!checkValidationLayerSupport()) {
            throw std::runtime_error("Validation layers requested, but not available!");
        }
#endif
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = name;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();
#ifdef NDEBUG
        createInfo.enabledLayerCount = 0;
#else
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
#endif
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create a Vulkan instance!");
        }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL Instance::debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT /*messageSeverity*/,
            VkDebugUtilsMessageTypeFlagsEXT /*messageType*/,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* /*pUserData*/) {

        std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

    void Instance::destroyDebugUtilsMessengerEXT(const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }

    std::vector<VkPhysicalDevice> Instance::enumerate_physical_devices() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0) {
            throw std::runtime_error("Failed to find GPUs with Vulkan support!");
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
        // https://stackoverflow.com/questions/15704565/efficient-way-to-return-a-stdvector-in-c
        return devices;
    }

    std::shared_ptr<PhysicalDevice> Instance::getPhysicalDevice(Surface *surface) {
        return PhysicalDevice::create(shared_from_this(), surface);
    }

    std::vector<const char*> Instance::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
#ifndef NDEBUG
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
        return extensions;
    }

    std::shared_ptr<Surface> Instance::getSurface(GLFWwindow *window) {
        return Surface::create(shared_from_this(), window);
    }

    void Instance::setupDebugMessenger() {
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr; // Optional

        if (createDebugUtilsMessengerEXT(&createInfo, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("Failed to set up debug messenger!");
        }
    }
}
