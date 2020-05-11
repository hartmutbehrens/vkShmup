//
// Created by hartmut on 2020/05/10.
//
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char** av)
{
    MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    return CommandLineTestRunner::RunAllTests(ac, av);
}