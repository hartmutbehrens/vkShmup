//
// Created by hartmut on 2020/04/27.
//
#include <fstream>
#include <iostream>
#include "vkShmup/Vk/ShaderModule.h"

namespace vkShmup {
    std::unique_ptr<ShaderModule> ShaderModule::create(const char *spirvFilename, const VkDevice& device) {
        return std::unique_ptr<ShaderModule>(new ShaderModule(spirvFilename, device));
    }

    ShaderModule::ShaderModule(const char* spirvFilename, const VkDevice& device): logicalDevice{device} {
        // http://www.gotw.ca/gotw/066.htm
        try {
            auto shaderCode = readFile(spirvFilename);
            createShaderModule(shaderCode);
        } catch  (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
    }

    ShaderModule::~ShaderModule() {
        vkDestroyShaderModule(logicalDevice, shaderModule, nullptr);
    }

    const VkShaderModule& ShaderModule::handle() const {
        return shaderModule;
    }

    void ShaderModule::createShaderModule(const std::vector<char> &code) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
        if (vkCreateShaderModule(logicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create shader module!");
        }
    }

    std::vector<char> ShaderModule::readFile(const char *spirvFilename) {
        std::ifstream file(spirvFilename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error(std::string("Failed to open file: ") + spirvFilename);
        }
        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer;
    }
}

