//
// Created by hartmut on 2020/04/25.
//

#ifndef VKSHMUP_PIPELINE_H
#define VKSHMUP_PIPELINE_H
#include <glm/glm.hpp>
#include <array>
#include <memory>
#include <optional>     // C++17
#include <vector>
#include "vkShmup/Vk/Instance.h"
#include "vkShmup/Vk/VMAllocator.h"

struct GLFWwindow;
namespace vkShmup {
    struct Vertex {
        glm::vec2 pos;
        glm::vec3 color;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            return attributeDescriptions;
        }
    };

    class Window;
    class Pipeline {
    public:
        using unique_ptr = std::unique_ptr<Pipeline>;
        static unique_ptr create(const char* name);
        void initVulkan(GLFWwindow* window);
        VkPhysicalDevice* physicalDeviceHandle();
        VkDevice* logicalDeviceHandle();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createVMAllocator();
        void createSurface(GLFWwindow* window);
        void createSwapChain(GLFWwindow* window);
        void createImageViews();
        void createRenderPass();
        void createGraphicsPipeline();
        void createFramebuffers();
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VmaAllocationCreateInfo allocInfo, VkBuffer& buffer, VmaAllocation& bufferMemory);
        void createVertexBuffer();
        void createCommandPool();
        void createCommandBuffers();
        void createSyncObjects();
        void drawFrame(GLFWwindow* window);
        void cleanupSwapChain();
        void recreateSwapChain(GLFWwindow* window);
        void frameBufferResized();
        ~Pipeline();

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

    protected:
        Pipeline();
        explicit Pipeline(const char* name);

    private:
        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        bool isDeviceSuitable(VkPhysicalDevice device);
        static std::vector<const char*> getRequiredExtensions();
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
        // members


        Instance::unique_ptr instance;
        VkSurfaceKHR surface;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice logicalDevice;
        VMAllocator::unique_ptr vmAllocator = nullptr;

        VkQueue graphicsQueue;
        VkQueue presentQueue;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        VkBuffer vertexBuffer;
        VmaAllocation vertexBufferMemory;
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;
        bool framebufferResized = false;
    };
}

#endif //VKSHMUP_PIPELINE_H
