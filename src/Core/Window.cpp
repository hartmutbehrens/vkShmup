//
// Created by hartmut on 2020/04/26.
//
#include "vkShmup/Core/Window.h"

#include <utility>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

namespace vkShmup {

    GLFWwindow * Window::handle() const {
        return w;
    }

    Window::unique_ptr Window::create(std::string name) {
        return std::unique_ptr<Window, GLFWwindowDestroyer>(new Window(std::move(name)), GLFWwindowDestroyer());
    }

    Window::Window(): name{"application"}, width{WIDTH}, height{HEIGHT} {
        w = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    }

    Window::Window(std::string name): name{name}, width{WIDTH}, height{HEIGHT} {
        w = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    }
}

