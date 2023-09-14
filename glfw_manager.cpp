
#include "glfw_manager.h"

#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <stdexcept>


static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

glfw_manager::glfw_manager() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        throw std::runtime_error("Cannot initialize glfw!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
}

glfw_manager::~glfw_manager() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void glfw_manager::create_window(int width, int height, std::string_view app_title) {
    window_ = glfwCreateWindow(width, height, app_title.data(), nullptr, nullptr);
    if (window_ == nullptr) {
        throw std::runtime_error("Cannot create glfw window!");
    }
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // Enable vsync
}

GLFWwindow *glfw_manager::get_window() const {
    return window_;
}
