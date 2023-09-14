#pragma once

#include <memory>

struct ImGuiIO;
struct ImVec4;

class glfw_manager;

class test_application {
public:
    test_application();

    ~test_application();

    static void start_frame();

    static bool create_window(ImGuiIO &io, float *clear_color);


    void render(ImVec4 &clear_color);

    void start();

private:
    static void show_next_window(bool &show_another_window);

    std::unique_ptr<glfw_manager> glfwManager_;
};
