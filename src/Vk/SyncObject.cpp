//
// Created by hartmut on 2020/04/28.
//
#include <type_traits>
#include <vulkan/vulkan.h>
#include "vkShmup/Vk/SyncObject.h"

namespace vkShmup {
    template <typename T>
    template <typename B>
    std::unique_ptr<SyncObject<T>> SyncObject<T>::create(B& createInfo, const VkDevice& device) {
        static_assert(std::is_same_v<T, VkSemaphore> || std::is_same_v<T, VkFence >, "Only VkSemaphore or VkFence are allowed.");
        return std::unique_ptr<SyncObject<T>>(new SyncObject<T>(createInfo, device));
    }

    template <typename T>
    template <typename B>
    SyncObject<T>::SyncObject(B &createInfo, const VkDevice &device): logicalDevice{device} {
        if constexpr(std::is_same_v<T, VkSemaphore>) {
            if (vkCreateSemaphore(logicalDevice, &createInfo, nullptr, &syncObject) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create a semaphore!");
            }
        }
        else {
            if (vkCreateFence(logicalDevice, &createInfo, nullptr, &syncObject) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create a fence!");
            }
        }
    }

    template <typename T>
    SyncObject<T>::~SyncObject() {
        if constexpr(std::is_same_v<T, VkSemaphore>) {
            vkDestroySemaphore(logicalDevice, syncObject, nullptr);
        }
        else {
            vkDestroyFence(logicalDevice, syncObject, nullptr);
        }
    }
}

