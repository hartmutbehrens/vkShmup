//
// Created by hartmut on 2020/04/25.
//

#ifndef VKSHMUP_APPLICATION_H
#define VKSHMUP_APPLICATION_H
#include "vkShmup/Core/Window.h"
#include "vkShmup/Vk/Pipeline.h"

struct GLFWwindow;
namespace vkShmup {
    class Application {
    public:
        Application();
        explicit Application(const char* name);
        ~Application() = default;
        void run();

    private:
        // methods
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        // members
        vkShmup::Window::unique_ptr window;
        vkShmup::Pipeline::unique_ptr pipeline;
    };
}

#endif //VKSHMUP_APPLICATION_H
