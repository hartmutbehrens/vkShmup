//
// Created by hartmut on 2020/04/28.
//

#ifndef VKSHMUP_SYNCOBJECT_H
#define VKSHMUP_SYNCOBJECT_H
#include <memory>
#include <vulkan/vulkan.h>

namespace vkShmup {
    template <typename T>
    class SyncObject {
    public:
        static std::unique_ptr<SyncObject> create(VkSemaphoreCreateInfo& semaphoreInfo, const VkDevice& device);
        static std::unique_ptr<SyncObject> create(VkFenceCreateInfo& fenceInfo, const VkDevice& device);
        SyncObject() = delete;
        ~SyncObject();
        [[nodiscard]] const T& handle() const {return syncObject;}
    protected:
        template <typename C>
        SyncObject(C& syncObjectInfo, const VkDevice& device);

    private:
        T syncObject;
        VkDevice logicalDevice;
    };
}

#endif //VKSHMUP_SYNCOBJECT_H
