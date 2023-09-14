#include "test_application.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glfw_manager.h"

#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include <memory>
#include <cmath>


test_application::test_application() : glfwManager_(std::make_unique<glfw_manager>()) {
    glfwManager_->create_window(1280, 720, "Dear ImGui GLFW+OpenGL3 example");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfwManager_->get_window(), true);
    constexpr std::string_view glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version.data());
}

test_application::~test_application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void test_application::start_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

bool test_application::create_window(ImGuiIO &io, float *clear_color) {
    static bool show_another_window = false;
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin(
            "Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", clear_color); // Edit 3 floats representing a color

    if (ImGui::Button(
            "Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    // Generate samples and plot them
    float samples[100];
    for (int n = 0; n < 100; n++)
        samples[n] = sinf(float(n) * 0.2f + float(ImGui::GetTime()) * 1.5f);
    ImGui::PlotLines("Samples", samples, 100);

    ImGui::End();

    if (show_another_window) {
        show_next_window(show_another_window);
    }
}

void test_application::show_next_window(bool &show_another_window) {
    ImGui::Begin("Another Window",
                 &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
        show_another_window = false;
    ImGui::End();
}

void test_application::render(ImVec4 &clear_color) {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(glfwManager_->get_window(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void test_application::start() {
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    while (!glfwWindowShouldClose(glfwManager_->get_window())) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        start_frame();

        create_window(io, reinterpret_cast<float *>(&clear_color));

        render(clear_color);

        glfwSwapBuffers(glfwManager_->get_window());
    }
}
