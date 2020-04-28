//
// Created by hartmut on 2020/04/27.
//

#ifndef VKSHMUP_SHADERMODULE_H
#define VKSHMUP_SHADERMODULE_H
#include <vulkan/vulkan.h>
#include <memory>
#include <vector>

namespace vkShmup {
    // these methods are not lumped together with Pipeline because the VkShaderModule
    // has a different lifetime compared to the other pipeline components
    class ShaderModule {
    public:
        static std::unique_ptr<ShaderModule> create(const char* spirvFilename, VkDevice* device);
        ShaderModule() = delete;
        ~ShaderModule();
        VkShaderModule* handle();

    protected:
        ShaderModule(const char* spirvFilename, VkDevice* device);
        void createShaderModule(const std::vector<char>& code);
    private:
        static std::vector<char> readFile(const char* spirvFilename);
        // members
        VkShaderModule shaderModule;
        VkDevice* logicalDevice;
    };

}

#endif //VKSHMUP_SHADERMODULE_H
