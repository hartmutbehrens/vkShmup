//
// Created by hartmut on 2020/05/06.
//
#include <cassert>
#include <set>
#include <string>
#include "vkShmup/Vk/PhysicalDevice.h"
#include "vkShmup/Vk/Instance.h"

namespace vkShmup {
    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    PhysicalDevice::unique_ptr PhysicalDevice::create(vkShmup::Instance *instance) {
        assert(instance != nullptr);
        return PhysicalDevice::unique_ptr(new PhysicalDevice(instance));
    }

    PhysicalDevice::PhysicalDevice(Instance* instance)  {
        for (const auto& d : instance->enumerate_physical_devices()) {
            if (isDeviceSuitable(d)) {
                physicalDevice = d;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("Failed to find a suitable GPU!");
        }
    }

    bool PhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    PhysicalDevice::QueueFamilyIndices PhysicalDevice::findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;
        // Assign index to queue families that could be found


        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
//        int i = 0;
//        for (const auto& queueFamily : queueFamilies) {
//            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
//                indices.graphicsFamily = i;
//            }
//            VkBool32 presentSupport = false;
//            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
//            if (presentSupport) {
//                indices.presentFamily = i;
//            }
//            if (indices.isComplete()) {
//                break;
//            }
//            i++;
//        }
        return indices;
    }

    bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndices indices = findQueueFamilies(device);

        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        bool extensionsSupported = checkDeviceExtensionSupport(device);
        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return indices.isComplete() && extensionsSupported && swapChainAdequate && (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    }

    PhysicalDevice::SwapChainSupportDetails PhysicalDevice::querySwapChainSupport(VkPhysicalDevice device) {
        SwapChainSupportDetails details;
//        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
//
//        uint32_t formatCount;
//        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
//        if (formatCount != 0) {
//            details.formats.resize(formatCount);
//            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
//        }
//
//        uint32_t presentModeCount;
//        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
//        if (presentModeCount != 0) {
//            details.presentModes.resize(presentModeCount);
//            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
//        }

        return details;
    }
}
