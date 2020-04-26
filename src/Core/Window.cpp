//
// Created by hartmut on 2020/04/26.
//
#include "vkShmup/Core/Window.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

namespace vkShmup {

    GLFWwindow * Window::handle() const {
        return w;
    }

    Window::unique_ptr Window::create(std::string name) {
        return std::unique_ptr<Window, GLFWwindowDestroyer>(new Window(name), GLFWwindowDestroyer());
    }

    Window::Window(): name{"application"} {
        w = glfwCreateWindow(WIDTH, HEIGHT, name.c_str(), nullptr, nullptr);
    }

    Window::Window(std::string name): name{name} {
        w = glfwCreateWindow(WIDTH, HEIGHT, name.c_str(), nullptr, nullptr);
    }

    Window::~Window() {
    }
}

