//
// Created by hartmut on 2020/05/16.
//
#include <set>
#include "vkShmup/Vk/PhysicalDevice.h"
#include "vkShmup/Vk/Device.h"
#include "vkShmup/Vk/VMAllocator.h"

namespace vkShmup {

    std::shared_ptr<Device> Device::create(std::shared_ptr<PhysicalDevice> p){
        return std::shared_ptr<Device>(new Device(p));
    }

    std::unique_ptr<VMAllocator> Device::createVMAllocator() {
        return VMAllocator::create(physicalDevice->instanceHandle(), physicalDevice->handle(), shared_from_this());
    }

    Device::Device(std::shared_ptr<PhysicalDevice> p): physicalDevice(p) {
        QueueFamilyIndices indices = physicalDevice->getQueueFamilies();

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

#ifdef NDEBUG
        createInfo.enabledLayerCount = 0;
#else
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
#endif
        if (vkCreateDevice(physicalDevice->handle(), &createInfo, nullptr, &device) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create logical device!");
        }
        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQ);
        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQ);
    }

    Device::~Device() {
        vkDestroyDevice(device, nullptr);
    }

}