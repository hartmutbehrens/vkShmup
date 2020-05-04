//
// Created by hartmut on 2020/05/02.
//
// Inject Vulkan Memory Allocator impl
#define VMA_IMPLEMENTATION

#include "vkShmup/Vk/VMAllocator.h"


namespace vkShmup {
    VMAllocator::unique_ptr VMAllocator::create(const VkInstance &instance, const VkPhysicalDevice& physicalDevice, const VkDevice& device) {
        return VMAllocator::unique_ptr(new VMAllocator(instance, physicalDevice, device));
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
