//
// Created by hartmut on 2020/04/25.
//
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "vkShmup/Core/Application.h"
#include "vkShmup/Core/Window.h"
#include "vkShmup/Vk/Pipeline.h"

namespace vkShmup {

    Application::Application(): Application("application") {
    }

    Application::Application(const char* name):
            window(Window::create(name)),
            pipeline(Pipeline::create(name)) {
        pipeline->initVulkan(window->handle());
        glfwSetWindowUserPointer(window->handle(), &pipeline);
        glfwSetFramebufferSizeCallback(window->handle(), framebufferResizeCallback);
    }

    // public methods
    void Application::run() {
        while (!glfwWindowShouldClose(window->handle())) {
            glfwPollEvents();
            pipeline->drawFrame(window->handle());
        }
        vkDeviceWaitIdle(pipeline->deviceHandle());
    }

    void Application::framebufferResizeCallback(GLFWwindow* window, int /*width*/, int /*height*/) {
        auto p = reinterpret_cast<Pipeline*>(glfwGetWindowUserPointer(window));
        if (p != nullptr) {
            p->frameBufferResized();
        }

    }

} // namespace vkShmup

