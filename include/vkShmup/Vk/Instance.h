//
// Created by hartmut on 2020/05/05.
//

#ifndef VKSHMUP_INSTANCE_H
#define VKSHMUP_INSTANCE_H
#include <memory>
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vkShmup {
    extern const std::vector<const char*> validationLayers;

    class PhysicalDevice;
    class Surface;
    class Instance: public std::enable_shared_from_this<Instance> {
    public:
        static std::shared_ptr<Instance> create(const char* name);
        [[nodiscard]] const VkInstance& handle() const { return instance; }
        ~Instance();

        static bool checkValidationLayerSupport();
        VkResult createDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator);
        void createInstance(const char* name);
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData);
        void destroyDebugUtilsMessengerEXT(const VkAllocationCallbacks* pAllocator);
        std::vector<VkPhysicalDevice> enumerate_physical_devices();
        std::shared_ptr<PhysicalDevice> getPhysicalDevice(Surface* surface);
        static std::vector<const char*> getRequiredExtensions();
        std::shared_ptr<Surface> getSurface(GLFWwindow* window);

        void setupDebugMessenger();

    protected:
        explicit Instance(const char* name);

    private:
        VkInstance instance;
#ifndef NDEBUG
        VkDebugUtilsMessengerEXT debugMessenger;
#endif
    };
}

#endif //VKSHMUP_INSTANCE_H
