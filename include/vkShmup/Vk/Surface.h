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

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class Instance;
    class Surface {
    public:
        static std::shared_ptr<Surface> create(std::shared_ptr<Instance> i, GLFWwindow* window);
        [[nodiscard]] const VkSurfaceKHR& handle() const { return surface; }
        ~Surface();

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    protected:
        explicit Surface(std::shared_ptr<Instance> i, GLFWwindow* window);

    private:
        std::shared_ptr<Instance> instance;
        VkSurfaceKHR surface;
    };

}

#endif //VKSHMUP_SURFACE_H
