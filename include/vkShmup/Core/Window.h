//
// Created by hartmut on 2020/04/26.
//
#ifndef VKSHMUP_WINDOW_H
#define VKSHMUP_WINDOW_H
#include <memory>
// forward declaration
struct GLFWwindow;

namespace vkShmup {
    class Window {
    public:
        using unique_ptr = std::unique_ptr<Window>;
        static unique_ptr create(const char* name);
        [[nodiscard]] GLFWwindow* handle() const;
        ~Window();

    protected:
        Window();
        explicit Window(const char* name);

    private:
        GLFWwindow *w;
    };
}

#endif //VKSHMUP_WINDOW_H
