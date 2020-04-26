//
// Created by hartmut on 2020/04/26.
//
#ifndef VKSHMUP_WINDOW_H
#define VKSHMUP_WINDOW_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

namespace vkShmup {
    class Window {
    public:
        struct GLFWwindowDestroyer {
            void operator()(Window *win) { glfwDestroyWindow(win->window()); }
        };

        static auto create(std::string name) {
            return std::unique_ptr<Window, GLFWwindowDestroyer>(new Window(name), GLFWwindowDestroyer());
        }
        using unique_ptr = std::unique_ptr<Window, GLFWwindowDestroyer>;

        GLFWwindow* window() const;
        ~Window();

    protected:
        Window();
        Window(std::string name);

    private:
        GLFWwindow *w;
        std::string name;
    };
}

#endif //VKSHMUP_WINDOW_H
