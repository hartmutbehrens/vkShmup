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
        static std::shared_ptr<PhysicalDevice> create(std::shared_ptr<Instance> i, Surface* surface);
        [[nodiscard]] const VkPhysicalDevice& handle() const { return physicalDevice; }
        ~PhysicalDevice() = default;

        QueueFamilyIndices getQueueFamilies();

    protected:
        PhysicalDevice(std::shared_ptr<Instance> i, Surface* surface);

    private:

        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, Surface* surface);
        static VkBool32 hasPhysicalDeviceSurfaceSupport(VkPhysicalDevice physicalDevice, Surface* surface, uint32_t queueFamilyIndex);
        static bool isDeviceSuitable(VkPhysicalDevice device, QueueFamilyIndices indices, Surface* surface);

        std::shared_ptr<Instance> instance;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        QueueFamilyIndices queueIndices;
    };
}

#endif //VKSHMUP_PHYSICALDEVICE_H
