//
// Created by hartmut on 2020/04/25.
//
#include "vkShmup/Core/Application.h"
#include "vkShmup/Core/Window.h"
#include "vkShmup/Vk/Instance.h"

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

namespace vkShmup {

    Application::Application(): name("application") {
    }

    Application::Application(std::string name): name(name) {
    }

    // public methods
    void Application::run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

    //private methods
    void Application::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);   // don't create an OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = Window::create(name);
    }

    void Application::initVulkan() {
        vkShmup::Instance::create(instance, name);
        if (enableValidationLayers) {
            vkShmup::Instance::setupDebugMessenger(instance, debugMessenger);
        }
    }

    void Application::mainLoop() {
        while (!glfwWindowShouldClose(window->window())) {
            glfwPollEvents();
        }
    }

    void Application::cleanup() {
        if (enableValidationLayers) {
            Instance::DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }
        vkDestroyInstance(instance, nullptr);
        glfwTerminate();
    }

} // namespace vkShmup

