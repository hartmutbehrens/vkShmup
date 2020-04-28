//
// Created by hartmut on 2020/04/28.
//
#include <type_traits>
#include <vulkan/vulkan.h>
#include "vkShmup/Vk/SyncObject.h"

namespace vkShmup {
    template <typename T>
    std::unique_ptr<SyncObject<T>> SyncObject<T>::create(VkSemaphoreCreateInfo& semaphoreInfo, const VkDevice& device) {
        return std::unique_ptr<SyncObject>(new SyncObject(semaphoreInfo, device));
    }

    template <typename T>
    std::unique_ptr<SyncObject<T>> SyncObject<T>::create(VkFenceCreateInfo& fenceInfo, const VkDevice& device) {
        return std::unique_ptr<SyncObject>(new SyncObject(fenceInfo, device));
    }

    template <typename T>
    template <typename C>
    SyncObject<T>::SyncObject(C &syncObjectInfo, const VkDevice &device): logicalDevice{device} {
        if constexpr(std::is_same_v<T, VkSemaphore>) {
            if (vkCreateSemaphore(logicalDevice, &syncObjectInfo, nullptr, &syncObject) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create a semaphore!");
            }
        }
        else {
            if (vkCreateFence(logicalDevice, &syncObjectInfo, nullptr, &syncObject) != VK_SUCCESS) {
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

