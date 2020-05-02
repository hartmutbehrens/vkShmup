//
// Created by hartmut on 2020/05/02.
//
// Inject Vulkan Memory Allocator impl
#define VMA_IMPLEMENTATION
#include "vkShmup/Vk/VMAllocator.h"


namespace vkShmup {
    std::unique_ptr<VMAllocator> VMAllocator::create(const VkInstance &instance, const VkPhysicalDevice& physicalDevice, const VkDevice& device) {
        return std::unique_ptr<VMAllocator>(new VMAllocator(instance, physicalDevice, device));
    }

    VMAllocator::VMAllocator(const VkInstance &instance, const VkPhysicalDevice& physicalDevice, const VkDevice& device)
            : allocator(nullptr) {
        VmaAllocatorCreateInfo allocatorInfo = {};
        allocatorInfo.physicalDevice = physicalDevice;
        allocatorInfo.device = device;
        allocatorInfo.instance = instance;
        vmaCreateAllocator(&allocatorInfo, &allocator);
    }

    VMAllocator::~VMAllocator() {
        vmaDestroyAllocator(allocator);
        allocator = nullptr;
    }

}
