//
// Created by hartmut on 2020/05/10.
//
// NB: include your own header files before including CppUTest/TestHarness.h
// also don't forget to set ENV vars for: VULKAN_SDK_PATH, VK_LAYER_PATH, LD_LIBRARY_PATH
// TODO: find better way of doing this
#include "vkShmup/Core/Window.h"
#include "vkShmup/Vk/Instance.h"
#include "vkShmup/Vk/Pipeline.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(TestApp)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(TestApp, CanCreateWindow)
{
    auto window = vkShmup::Window::create("test_window");
}

TEST(TestApp, CanCreateInstance)
{
    // https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/issues/1298
    auto instance = vkShmup::Instance::create("test_instance");
}

