#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "vkShmup/Core/Application.h"

int main() {
    vkShmup::Application app{"vkShmup"};

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}