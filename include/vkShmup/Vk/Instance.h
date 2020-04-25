//
// Created by hartmut on 2020/04/25.
//

#ifndef VKSHMUP_INSTANCE_H
#define VKSHMUP_INSTANCE_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

namespace vkShmup {
    class Instance {
    public:
        static bool checkValidationLayerSupport();
        static void create(VkInstance &instance, std::string name);
        static std::vector<VkExtensionProperties> extensions();

    protected:
        Instance() = default;
    };
}

#endif //VKSHMUP_INSTANCE_H
