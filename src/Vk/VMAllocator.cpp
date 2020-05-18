//
// Created by hartmut on 2020/05/02.
//
// Inject Vulkan Memory Allocator impl
#define VMA_IMPLEMENTATION

#include "vkShmup/Vk/Device.h"
#include "vkShmup/Vk/VMAllocator.h"

namespace vkShmup {
    std::unique_ptr<VMAllocator> VMAllocator::create(const VkInstance &instance, const VkPhysicalDevice& physicalDevice, std::shared_ptr<Device> d) {
        return std::unique_ptr<VMAllocator>(new VMAllocator(instance, physicalDevice, d));
    }

    VMAllocator::VMAllocator(const VkInstance &instance, const VkPhysicalDevice& physicalDevice, std::shared_ptr<Device> d)
            : device{d},
              allocator{nullptr} {
        VmaAllocatorCreateInfo allocatorInfo = {};
        allocatorInfo.physicalDevice = physicalDevice;
        allocatorInfo.device = device->handle();
        allocatorInfo.instance = instance;
        vmaCreateAllocator(&allocatorInfo, &allocator);
    }

    VMAllocator::~VMAllocator() {
        vmaDestroyAllocator(allocator);
        allocator = nullptr;
    }
}
