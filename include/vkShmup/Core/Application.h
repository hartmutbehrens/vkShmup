//
// Created by hartmut on 2020/04/25.
//

#ifndef VKSHMUP_APPLICATION_H
#define VKSHMUP_APPLICATION_H
#include <string>
#include "vkShmup/Core/Window.h"
#include "vkShmup/Vk/Instance.h"

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

        // members
        std::string name;
        vkShmup::Window::unique_ptr window;
        vkShmup::Instance::unique_ptr instance;

    };
}

#endif //VKSHMUP_APPLICATION_H
