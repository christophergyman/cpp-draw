#define GL_SILENCE_DEPRECATION

#include "shaders.h"
#include "glfwWindowCreation.h"
#include <iostream>

// ImGui includes
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void renderTriangles(unsigned int shaderProgram, unsigned int VAO) {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void imguiInit(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
    const char *glsl_version =
        "#version 150"; // Adjust this based on your OpenGL version
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void imguiCleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void imguiWindow(GLFWwindow *window, bool &show_demo_window,
                 bool &show_another_window, ImVec4 &clear_color) {
    // Get ImGuiIO for framerate access
    ImGuiIO &io = ImGui::GetIO();
    
    // Check if window is minimized
    if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
        ImGui_ImplGlfw_Sleep(10);
        return; // Don't render if minimized
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui Demo Window
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // Custom ImGui window
    {
        static float triangle_color[3] = {1.0f, 1.0f, 1.0f};
        static int counter = 0;

        ImGui::Begin("OpenGL Controls");
        ImGui::Text("This is your OpenGL application with ImGui!");
        ImGui::Checkbox("Demo Window", &show_demo_window);
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::ColorEdit3("Triangle Color", triangle_color);
        ImGui::ColorEdit3("Clear Color", (float *)&clear_color);

        if (ImGui::Button("Button"))
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // Another window
    if (show_another_window) {
        ImGui::Begin("Another Window", &show_another_window);
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

    // Render ImGui
    ImGui::Render();
}

int main() {
    GLFWwindow *window = glfw_window_creation();

    // Fixed: Pass window directly, not *window
    imguiInit(window);

    Shaders shader = init_and_compile_shaders();
    unsigned int shaderProgram;
    unsigned int VBO;
    unsigned int VAO;
    shaderProgram = shader.shaderProgram;
    VBO = shader.VBO;
    VAO = shader.VAO;
    std::cout << "SUCCESS::INITIALISATION::COMPLETE \n";

    // ImGui variables
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color =
        ImVec4(0.2f, 0.3f, 0.3f, 1.00f); // Match your original clear color

    // main loop render
    std::cout << "STARTING::RENDERING::LOOP \n";
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        // Process input only if ImGui doesn't want to capture it
        processInput(window);

        // Set up viewport and clear
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, 
                     clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render your triangles
        renderTriangles(shaderProgram, VAO);
        
        // Fixed: Pass all required parameters to imguiWindow
        imguiWindow(window, show_demo_window, show_another_window, clear_color);
        
        // Render ImGui draw data
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // clean up and terminate
    imguiCleanup();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    std::cout << "SUCCESS::TERMINATION::COMPLETE \n";

    return 0;
}
