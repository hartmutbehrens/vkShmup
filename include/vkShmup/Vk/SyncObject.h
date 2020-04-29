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
        template <typename B>
        static std::unique_ptr<SyncObject> create(B& createInfo, const VkDevice& device);
        SyncObject() = delete;
        ~SyncObject();
        [[nodiscard]] const T& handle() const {return syncObject;}
    protected:
        template <typename B>
        SyncObject(B& createInfo, const VkDevice& device);

    private:
        T syncObject;
        VkDevice logicalDevice;
    };
}

#endif //VKSHMUP_SYNCOBJECT_H
