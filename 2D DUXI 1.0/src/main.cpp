#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Callback for resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Global variables for camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
float lastX = 400, lastY = 300;
bool firstMouse = true;

// Mouse callback
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xOffset, yOffset);
}

// Scroll callback
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    camera.processMouseScroll(yOffset);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Game Engine", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Set callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Capture the mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Load shaders
    Shader shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    // Define vertices for a triangle
    float vertices[] = {
        // Positions         // Colors
         0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // Top vertex (red)
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // Bottom-left vertex (green)
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // Bottom-right vertex (blue)
    };

    // Create VAO and VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Handle input
        float currentFrame = glfwGetTime();
        static float lastFrame = 0.0f;
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.processKeyboard(Camera::Movement::FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.processKeyboard(Camera::Movement::BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.processKeyboard(Camera::Movement::LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.processKeyboard(Camera::Movement::RIGHT, deltaTime);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader program
        shader.use();

        // Pass view and projection matrices to the shader
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix(800.0f / 600.0f);
        shader.setUniform("view", view);
        shader.setUniform("projection", projection);

        // Render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}