#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "vkShmup/Application.h"

int main() {
    vkShmup::Application app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}