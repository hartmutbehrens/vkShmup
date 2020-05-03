//
// Created by hartmut on 2020/05/02.
//

#ifndef VKSHMUP_VMALLOCATOR_H
#define VKSHMUP_VMALLOCATOR_H

#include <memory>
#include "VulkanMemoryAllocator/vk_mem_alloc.h"

namespace vkShmup {
    class VMAllocator {
    public:
        struct VmaDestroyer {
            void operator()(VMAllocator* vma) {
                vmaDestroyAllocator(vma->allocator);
                vma->allocator = nullptr;
            }
        };
        using unique_ptr = std::unique_ptr<VMAllocator, VmaDestroyer>;
        static unique_ptr create(const VkInstance &instance, const VkPhysicalDevice& physicalDevice, const VkDevice& device);
        [[nodiscard]] const VmaAllocator& handle() const { return allocator; }
    protected:
        VMAllocator(const VkInstance &instance, const VkPhysicalDevice& physicalDevice, const VkDevice& device);
    private:
        VmaAllocator allocator;
    };

}

#endif //VKSHMUP_VMALLOCATOR_H
