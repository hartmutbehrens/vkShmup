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
            void operator()(Window *win) { glfwDestroyWindow(win->handle()); }
        };
        using unique_ptr = std::unique_ptr<Window, GLFWwindowDestroyer>;
        static unique_ptr create(std::string name);

        GLFWwindow* handle() const;
        ~Window();

    protected:
        Window();
        Window(std::string name);

    private:
        GLFWwindow *w;
        std::string name;
        uint32_t width;
        uint32_t height;
    };
}

#endif //VKSHMUP_WINDOW_H
