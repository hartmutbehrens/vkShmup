//
// Created by hartmut on 2020/04/25.
//
#include "vkShmup/Core/Application.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

namespace vkShmup {
    void Application::run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

    void Application::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);   // don't create an OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = std::unique_ptr<GLFWwindow, GLFWwindowDestroyer>(glfwCreateWindow(WIDTH, HEIGHT, "vkShmup", nullptr, nullptr));
    }

    void Application::initVulkan() {}

    void Application::mainLoop() {
        while (!glfwWindowShouldClose(window.get())) {
            glfwPollEvents();
        }
    }

    void Application::cleanup() {
        glfwTerminate();
    }

} // namespace vkShmup

