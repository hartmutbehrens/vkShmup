//
// Created by hartmut on 2020/04/25.
//

#ifndef VKSHMUP_INSTANCE_H
#define VKSHMUP_INSTANCE_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

namespace vkShmup {
    class Instance {
    public:
        static bool checkValidationLayerSupport();
        static void create(VkInstance& instance, std::string name);
        static std::vector<VkExtensionProperties> extensions();
        static std::vector<const char*> getRequiredExtensions();
        static void pickPhysicalDevice(VkInstance& instance, VkPhysicalDevice& device);
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData);
        static void setupDebugMessenger(VkInstance &instance, VkDebugUtilsMessengerEXT &debugMessenger);
        static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);



    protected:
        Instance() = default;

    private:
        static bool isDeviceSuitable(VkPhysicalDevice device);
    };
}

#endif //VKSHMUP_INSTANCE_H
