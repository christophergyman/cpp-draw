#define GL_SILENCE_DEPRECATION

#include "shaders.h"
#include "glfwWindowCreation.h"
#include <iostream>

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void render(){

}

int main() {

    GLFWwindow *window = glfw_window_creation();
    Shaders shader = init_and_compile_shaders();
    unsigned int shaderProgram;
    unsigned int VBO;
    unsigned int VAO;

    shaderProgram = shader.shaderProgram;
    VBO = shader.VBO;
    VAO = shader.VAO;

    // main loop render
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
