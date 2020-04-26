//
// Created by hartmut on 2020/04/25.
//

#ifndef VKSHMUP_INSTANCE_H
#define VKSHMUP_INSTANCE_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>
#include <optional>     // C++17
#include <string>
#include <vector>

namespace vkShmup {
    class Instance {
    public:
        using unique_ptr = std::unique_ptr<Instance>;
        static unique_ptr create(std::string name);
        VkInstance* instanceHandle();
        VkPhysicalDevice* deviceHandle();
        void pickPhysicalDevice();
        ~Instance();

        struct QueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;

            bool isComplete() {
                return graphicsFamily.has_value();
            }
        };


    protected:
        Instance();
        explicit Instance(std::string name);

    private:
        void createInstance(std::string name = {"application"});

        static bool isDeviceSuitable(VkPhysicalDevice device);
        static std::vector<const char*> getRequiredExtensions();
        static bool checkValidationLayerSupport();

        template <typename T>
        void setupDebugMessenger(T callback);

        static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData);
        static std::vector<VkExtensionProperties> extensions();
        static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        // members
        VkInstance instance;
        VkPhysicalDevice physicalDevice;
        VkDebugUtilsMessengerEXT debugMessenger;
    };
}

#endif //VKSHMUP_INSTANCE_H
