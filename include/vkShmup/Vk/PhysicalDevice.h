//
// Created by hartmut on 2020/05/06.
//

#ifndef VKSHMUP_PHYSICALDEVICE_H
#define VKSHMUP_PHYSICALDEVICE_H
#include <optional>     // C++17
#include <vector>
#include <memory>
#include <vulkan/vulkan_core.h>

namespace vkShmup {
    extern const std::vector<const char*> deviceExtensions;
    class Instance;
    class Surface;

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class PhysicalDevice {
    public:
        static std::unique_ptr<PhysicalDevice> create(Instance* instance, Surface* surface);
        [[nodiscard]] const VkPhysicalDevice& handle() const { return physicalDevice; }
        ~PhysicalDevice() = default;

        QueueFamilyIndices getQueueFamilies();

    protected:
        explicit PhysicalDevice(Instance* instance, Surface* surface);

    private:

        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, Surface* surface);
        VkBool32 hasPhysicalDeviceSurfaceSupport(VkPhysicalDevice physicalDevice, Surface* surface, uint32_t queueFamilyIndex);
        bool isDeviceSuitable(VkPhysicalDevice device, QueueFamilyIndices indices, Surface* surface);

        QueueFamilyIndices queueIndices;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    };
}

#endif //VKSHMUP_PHYSICALDEVICE_H
