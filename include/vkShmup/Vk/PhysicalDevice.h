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
    class Instance;
    class PhysicalDevice {
    public:
        using unique_ptr = std::unique_ptr<PhysicalDevice>;
        static unique_ptr create(Instance* instance);
        [[nodiscard]] const VkPhysicalDevice& handle() const { return physicalDevice; }
        ~PhysicalDevice() = default;

    protected:
        explicit PhysicalDevice(Instance* instance);

    private:
        struct QueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            bool isComplete() {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };

        struct SwapChainSupportDetails {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };

        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        bool isDeviceSuitable(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    };
}

#endif //VKSHMUP_PHYSICALDEVICE_H
