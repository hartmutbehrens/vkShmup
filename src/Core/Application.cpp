//
// Created by hartmut on 2020/04/25.
//
#include "vkShmup/Core/Application.h"
#include "vkShmup/Core/Window.h"
#include "vkShmup/Vk/Pipeline.h"

namespace vkShmup {

    Application::Application(): name("application") {
    }

    Application::Application(std::string name): name(std::move(name)) {
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

        window = Window::create(name.c_str());
    }

    void Application::initVulkan() {
        pipeline = Pipeline::create(name.c_str());
        pipeline->initVulkan(window.get());
    }

    void Application::mainLoop() {
        while (!glfwWindowShouldClose(window->handle())) {
            glfwPollEvents();
        }
    }

    void Application::cleanup() {
        glfwTerminate();
    }

} // namespace vkShmup

