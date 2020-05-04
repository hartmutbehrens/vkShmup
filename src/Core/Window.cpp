//
// Created by hartmut on 2020/04/26.
//
#include "vkShmup/Core/Window.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

namespace vkShmup {

    Window::unique_ptr Window::create(const char* name) {
        return std::unique_ptr<Window>(new Window(name));
    }

    GLFWwindow * Window::handle() const {
        return w;
    }

    Window::Window(): Window("window") {
    }

    Window::Window(const char* name) {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);   // don't create an OpenGL context
        w = glfwCreateWindow(WIDTH, HEIGHT, name, nullptr, nullptr);
    }

    Window::~Window() {
        glfwDestroyWindow(w);
        glfwTerminate();
    }
}

