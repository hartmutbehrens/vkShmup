#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "vkShmup/Core/Application.h"

int main() {
    try {
        vkShmup::Application app{"vkShmup"};
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}