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

    class PhysicalDevice {
    public:
        static std::unique_ptr<PhysicalDevice> create(Instance* instance, Surface* surface);
        [[nodiscard]] const VkPhysicalDevice& handle() const { return physicalDevice; }
        ~PhysicalDevice() = default;

    protected:
        explicit PhysicalDevice(Instance* instance, Surface* surface);

    private:

        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        bool isDeviceSuitable(VkPhysicalDevice device, Surface* surface);
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    };
}

#endif //VKSHMUP_PHYSICALDEVICE_H
