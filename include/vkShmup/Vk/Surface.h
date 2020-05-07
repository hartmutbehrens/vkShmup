//
// Created by hartmut on 2020/05/06.
//

#ifndef VKSHMUP_SURFACE_H
#define VKSHMUP_SURFACE_H

#include <memory>
#include <optional>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vkShmup {
    class Instance;

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class Surface {
    public:
        using unique_ptr = std::unique_ptr<Surface>;
        static unique_ptr create(Instance* i, GLFWwindow* window);
        [[nodiscard]] const VkSurfaceKHR& handle() const { return surface; }
        ~Surface();

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        VkBool32 hasPhysicalDeviceSurfaceSupport(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    protected:
        explicit Surface(Instance* i, GLFWwindow* window);

    private:
        Instance* instance;
        VkSurfaceKHR surface;
    };

}

#endif //VKSHMUP_SURFACE_H
