//
// Created by hartmut on 2020/04/25.
//
#include <iostream>
#include <vector>
#include "vkShmup/Core/Application.h"
#include "vkShmup/Vk/Instance.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

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

        window = std::unique_ptr<GLFWwindow, GLFWwindowDestroyer>(glfwCreateWindow(WIDTH, HEIGHT, name.c_str(), nullptr, nullptr));
    }

    void Application::initVulkan() {
        vkShmup::Instance::create(instance, name);
    }

    void Application::mainLoop() {
        while (!glfwWindowShouldClose(window.get())) {
            glfwPollEvents();
        }
    }

    void Application::cleanup() {
        vkDestroyInstance(instance, nullptr);
        glfwTerminate();
    }

} // namespace vkShmup

