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
            void operator()(Window *win) {
                glfwDestroyWindow(win->handle());
                glfwTerminate();
            }
        };
        using unique_ptr = std::unique_ptr<Window, GLFWwindowDestroyer>;
        static unique_ptr create(const char* name);

        [[nodiscard]] GLFWwindow* handle() const;
        VkExtent2D actualExtent() { return extent; }
        ~Window() = default;

    protected:
        Window();
        explicit Window(const char* name);

    private:
        GLFWwindow *w;
        VkExtent2D extent;
    };
}

#endif //VKSHMUP_WINDOW_H
