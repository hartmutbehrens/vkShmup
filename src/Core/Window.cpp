//
// Created by hartmut on 2020/04/26.
//
#include "vkShmup/Core/Window.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

namespace vkShmup {

    Window::unique_ptr Window::create(const char* name) {
        return std::unique_ptr<Window, GLFWwindowDestroyer>(new Window(name), GLFWwindowDestroyer());
    }

    GLFWwindow * Window::handle() const {
        return w;
    }

    Window::Window(): extent{WIDTH, HEIGHT} {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);   // don't create an OpenGL context
        w = glfwCreateWindow(extent.width, extent.height, "window", nullptr, nullptr);
    }

    Window::Window(const char* name): extent{WIDTH, HEIGHT} {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);   // don't create an OpenGL context
        w = glfwCreateWindow(extent.width, extent.height, name, nullptr, nullptr);
    }
}

