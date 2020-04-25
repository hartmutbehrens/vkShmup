cmake_minimum_required(VERSION 3.10)
project(vkShmup)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    # add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_compile_options(-Wall)
endif()

set(VULKAN_SDK_PATH "/home/hartmut/projects/vulkan-sdk/1.2.135.0/x86_64" CACHE STRING "Path to Vulkan SDK x86_64 directory")
find_package(glfw3 3.3 REQUIRED)

add_executable(vkShmup src/main.cpp)
link_directories(${VULKAN_SDK+PATH}/include)
target_link_libraries(vkShmup glfw vulkan)