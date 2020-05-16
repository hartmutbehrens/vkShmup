//
// Created by hartmut on 2020/05/06.
//
#include <cassert>
#include <set>
#include <string>
#include "vkShmup/Vk/Instance.h"
#include "vkShmup/Vk/PhysicalDevice.h"
#include "vkShmup/Vk/Surface.h"

namespace vkShmup {
    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    std::shared_ptr<PhysicalDevice> PhysicalDevice::create(std::shared_ptr<Instance> i, Surface* surface) {
        assert(i != nullptr);
        return std::shared_ptr<PhysicalDevice>(new PhysicalDevice(i, surface));
    }

    PhysicalDevice::PhysicalDevice(std::shared_ptr<Instance> i, Surface* surface): instance(i)  {
        for (const auto& d : instance->enumerate_physical_devices()) {
            auto indices = findQueueFamilies(d, surface);
            if (isDeviceSuitable(d, indices, surface)) {
                physicalDevice = d;
                queueIndices = indices;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("Failed to find a suitable GPU!");
        }
    }

    QueueFamilyIndices PhysicalDevice::getQueueFamilies() {
        return queueIndices;
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

    QueueFamilyIndices PhysicalDevice::findQueueFamilies(VkPhysicalDevice device, Surface* surface) {
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

            if (hasPhysicalDeviceSurfaceSupport(device, surface, i)) {
                indices.presentFamily = i;
            }
            if (indices.isComplete()) {
                break;
            }
            ++i;
        }
        return indices;
    }

    VkBool32 PhysicalDevice::hasPhysicalDeviceSurfaceSupport(VkPhysicalDevice device, Surface* surface, uint32_t queueFamilyIndex) {
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, queueFamilyIndex, surface->handle(), &presentSupport);
        return presentSupport;
    }

    bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device, QueueFamilyIndices indices, Surface* surface) {

        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        bool extensionsSupported = checkDeviceExtensionSupport(device);
        bool swapChainAdequate = false;
        if (extensionsSupported) {
            auto swapChainSupport = surface->querySwapChainSupport(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }
        return indices.isComplete() && extensionsSupported && swapChainAdequate && (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    }
}
