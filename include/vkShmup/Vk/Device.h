//
// Created by hartmut on 2020/05/16.
//

#ifndef VKSHMUP_DEVICE_H
#define VKSHMUP_DEVICE_H

#include <vector>
#include <memory>
#include <vulkan/vulkan_core.h>
#include <vk_mem_alloc.h>

namespace vkShmup {
    extern const std::vector<const char*> validationLayers;

    class PhysicalDevice;
    class VMAllocator;

    class Device: public std::enable_shared_from_this<Device> {
    public:
        static std::shared_ptr<Device> create(std::shared_ptr<PhysicalDevice> p);
        std::unique_ptr<VMAllocator> createVMAllocator();
        [[nodiscard]] const VkDevice& handle() const { return device; }
        [[nodiscard]] VkQueue& graphicsQueue() { return graphicsQ; }
        [[nodiscard]] VkQueue& presentQueue() { return presentQ; }
        ~Device();
    protected:
        explicit Device(std::shared_ptr<PhysicalDevice> p);

    private:
        std::shared_ptr<PhysicalDevice> physicalDevice;
        VkDevice device;

        VkQueue graphicsQ;
        VkQueue presentQ;
    };
}

#endif //VKSHMUP_DEVICE_H
