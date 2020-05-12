//
// Created by hartmut on 2020/05/06.
//
#include "vkShmup/Vk/Instance.h"
#include "vkShmup/Vk/Surface.h"

namespace vkShmup {

    std::shared_ptr<Surface> Surface::create(std::shared_ptr<Instance> i, GLFWwindow* window) {
        return std::shared_ptr<Surface>(new Surface(i, window));
    }

    Surface::Surface(std::shared_ptr<Instance> i, GLFWwindow* window): instance(i) {
        if (glfwCreateWindowSurface(instance->handle(), window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    Surface::~Surface() {
        vkDestroySurfaceKHR(instance->handle(), surface, nullptr);
    }

    QueueFamilyIndices Surface::findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;
        // Assign index to queue families that could be found


        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            if (hasPhysicalDeviceSurfaceSupport(device, i)) {
                indices.presentFamily = i;
            }
            if (indices.isComplete()) {
                break;
            }
            ++i;
        }
        return indices;
    }

    VkBool32 Surface::hasPhysicalDeviceSurfaceSupport(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex) {
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, &presentSupport);
        return presentSupport;
    }

    SwapChainSupportDetails Surface::querySwapChainSupport(VkPhysicalDevice device) {
        SwapChainSupportDetails details;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }
}
