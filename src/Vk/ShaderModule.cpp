//
// Created by hartmut on 2020/04/27.
//
#include <fstream>
#include "vkShmup/Vk/ShaderModule.h"

namespace vkShmup {
    std::unique_ptr<ShaderModule> ShaderModule::create(const char *sprFilename, VkDevice* device) {
        return std::unique_ptr<ShaderModule>(new ShaderModule(sprFilename, device));
    }

    ShaderModule::ShaderModule(const char* sprFilename, VkDevice* device): logicalDevice{device} {
        auto shaderCode = readFile(sprFilename);
        createShaderModule(shaderCode);
    }

    ShaderModule::~ShaderModule() {
        vkDestroyShaderModule(*logicalDevice, shaderModule, nullptr);
    }

    VkShaderModule* ShaderModule::handle() {
        return &shaderModule;
    }

    void ShaderModule::createShaderModule(const std::vector<char> &code) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
        if (vkCreateShaderModule(*logicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module!");
        }
    }

    std::vector<char> ShaderModule::readFile(const char *sprFilename) {
        std::ifstream file(sprFilename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error(std::string("Failed to open file: ") + sprFilename);
        }
        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer;
    }
}

