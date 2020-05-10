//
// Created by hartmut on 2020/05/10.
//
// NB: include your own header files before including CppUTest/TestHarness.h
// also don't forget to set ENV vars for: VULKAN_SDK_PATH, VK_LAYER_PATH, LD_LIBRARY_PATH
// TODO: find better way of doing this
#include "vkShmup/Core/Application.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(TestApp)
{
};

TEST(TestApp, CanCreateApp)
{
    vkShmup::Application app{"test"};

}

