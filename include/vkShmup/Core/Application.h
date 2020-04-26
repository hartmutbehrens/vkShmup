//
// Created by hartmut on 2020/04/25.
//

#ifndef VKSHMUP_APPLICATION_H
#define VKSHMUP_APPLICATION_H
#include <memory>
#include <string>
#include "vkShmup/Core/Window.h"

namespace vkShmup {
    class Application {
    public:
        Application();
        Application(std::string name);
        ~Application() = default;
        void run();

    private:
        // methods
        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();

        // members
        std::string name;
        vkShmup::Window::unique_ptr window;
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
    };
}

#endif //VKSHMUP_APPLICATION_H
