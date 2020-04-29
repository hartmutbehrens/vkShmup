//
// Created by hartmut on 2020/04/25.
//

#ifndef VKSHMUP_APPLICATION_H
#define VKSHMUP_APPLICATION_H
#include <string>
#include "vkShmup/Core/Window.h"
#include "vkShmup/Vk/Pipeline.h"

namespace vkShmup {
    class Application {
    public:
        Application();
        explicit Application(std::string name);
        ~Application() = default;
        void run();

    private:
        // methods
        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        // members
        std::string name;
        vkShmup::Window::unique_ptr window;
        vkShmup::Pipeline::unique_ptr pipeline;

    };
}

#endif //VKSHMUP_APPLICATION_H
