project(imgui_min)

cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)

add_executable(imgui_min
        main.cpp
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backend/imgui_impl_glfw.cpp
        imgui/backend/imgui_impl_opengl3.cpp
        glfw_manager.cpp glfw_manager.h test_application.cpp test_application.h)

target_include_directories(${PROJECT_NAME} PRIVATE imgui imgui/backend)

target_link_libraries(imgui_min
        GL
        dl
        pthread
        glfw)
