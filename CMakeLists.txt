cmake_minimum_required(VERSION 3.10)
project(vkShmup VERSION 1.0.0)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Werror)
endif()
# check for VULKAN_SDK_PATH path variable or set a default..
set(VULKAN_SDK_PATH $ENV{VULKAN_SDK_PATH})
if(EXISTS ${VULKAN_SDK_PATH})
    message("VULKAN_SDK_PATH = ${VULKAN_SDK_PATH}")
else()
    message(FATAL_ERROR "VULKAN_SDK_PATH = ${VULKAN_SDK_PATH} does not exist")
endif()

find_package(glfw3 3.3 REQUIRED)
add_library(Core
        src/Core/Application.cpp
        src/Core/Window.cpp)
add_library(Vk
        third_party/VulkanMemoryAllocator/vk_mem_alloc.h
        src/Vk/Instance.cpp
        src/Vk/PhysicalDevice.cpp
        src/Vk/Pipeline.cpp
        src/Vk/ShaderModule.cpp
        src/Vk/Surface.cpp
        src/Vk/SyncObject.cpp
        src/Vk/VMAllocator.cpp )

include_directories(include
        third_party)

add_executable(vkShmup
        src/main.cpp)
link_directories(${VULKAN_SDK_PATH}/include)
target_link_libraries(vkShmup Core Vk glfw vulkan)

# TODO: this only works on Linux for now..
add_custom_command(
        TARGET vkShmup POST_BUILD
        COMMAND export VULKAN_SDK_PATH=${VULKAN_SDK_PATH} && ${CMAKE_SOURCE_DIR}/GLSL/compile.sh
        COMMENT "Compiling shaders" VERBATIM)

add_custom_command(
        TARGET vkShmup POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/GLSL ${CMAKE_CURRENT_BINARY_DIR}/GLSL
        COMMENT "Copying shaders" VERBATIM)


# CppUTest
include(FetchContent)
FetchContent_Declare(
        CppUTest
        GIT_REPOSITORY https://github.com/cpputest/cpputest.git
        GIT_TAG        latest-passing-build # or use release tag, eg. v3.8
)
# Set this to ON if you want to have the CppUTests in your project as well.
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(CppUTest)

add_executable(run_tests
        tests/AllTests.cpp
        tests/TestApp.cpp)
target_link_libraries(run_tests PRIVATE CppUTest CppUTestExt Core Vk glfw vulkan)