#pragma once

#include <string_view>

struct GLFWwindow;

class glfw_manager {

public:
    glfw_manager();

    ~glfw_manager();

    void create_window(int width, int height, std::string_view app_title);

    [[nodiscard]] GLFWwindow *get_window() const;

private:
    GLFWwindow *window_ = nullptr;
};
