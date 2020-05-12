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

    PhysicalDevice::unique_ptr PhysicalDevice::create(vkShmup::Instance *instance, Surface* surface) {
        assert(instance != nullptr);
        return PhysicalDevice::unique_ptr(new PhysicalDevice(instance, surface));
    }

    PhysicalDevice::PhysicalDevice(Instance* instance, Surface* surface)  {
        for (const auto& d : instance->enumerate_physical_devices()) {
            if (isDeviceSuitable(d, surface)) {
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

    bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device, Surface* surface) {
        auto indices = surface->findQueueFamilies(device);

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
