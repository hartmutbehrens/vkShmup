//
// Created by hartmut on 2020/04/25.
//

#ifndef VKSHMUP_APPLICATION_H
#define VKSHMUP_APPLICATION_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

namespace vkShmup {
    class Application {
    public:
        void run();

    private:
        // nested class
        struct GLFWwindowDestroyer {
            void operator()(GLFWwindow *w) { glfwDestroyWindow(w); }
        };

        // methods
        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();

        // members
        std::unique_ptr<GLFWwindow, GLFWwindowDestroyer> window;
    };
}

#endif //VKSHMUP_APPLICATION_H
