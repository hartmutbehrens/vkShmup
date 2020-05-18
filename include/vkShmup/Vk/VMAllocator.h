//
// Created by hartmut on 2020/05/02.
//

#ifndef VKSHMUP_VMALLOCATOR_H
#define VKSHMUP_VMALLOCATOR_H

#include <memory>
#include <vk_mem_alloc.h>

namespace vkShmup {
    class Device;

    class VMAllocator {
    public:
        static std::unique_ptr<VMAllocator> create(const VkInstance &instance, const VkPhysicalDevice& physicalDevice, const VkDevice& device);
        [[nodiscard]] const VmaAllocator& handle() const { return allocator; }
        ~VMAllocator();
    protected:
        VMAllocator(const VkInstance &instance, const VkPhysicalDevice& physicalDevice, const VkDevice& device);
    private:
        // std::shared_ptr<Device> device;
        VmaAllocator allocator;
    };

}

#endif //VKSHMUP_VMALLOCATOR_H
