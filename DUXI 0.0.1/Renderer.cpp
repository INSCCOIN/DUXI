#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer() : shader(nullptr), mesh(nullptr), camera(nullptr), lastX(400), lastY(300), firstMouse(true) {
    // Constructor
}

Renderer::~Renderer() {
    // Destructor
}

bool Renderer::Initialize() {
    std::cout << "Initializing Renderer..." << std::endl;
    
    if (!window.Create()) {
        return false;
    }

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    shader = new Shader();
    shader->load("vertex_shader.glsl", "fragment_shader.glsl");

    std::vector<Vertex> vertices = {
        // Define your vertices here
    };

    std::vector<GLuint> indices = {
        // Define your indices here
    };

    mesh = new Mesh(vertices, indices);

    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

    glfwSetFramebufferSizeCallback(window.GetGLFWwindow(), framebufferSizeCallback);
    glfwSetCursorPosCallback(window.GetGLFWwindow(), mouseCallback);
    glfwSetScrollCallback(window.GetGLFWwindow(), scrollCallback);

    glfwSetInputMode(window.GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    std::cout << "Renderer initialized successfully" << std::endl;
    return true;
}

void Renderer::Run() {
    std::cout << "Running Renderer..." << std::endl;

    while (!glfwWindowShouldClose(window.GetGLFWwindow())) {
        // Main loop code
    }
}

void Renderer::Shutdown() {
    // Cleanup code
}

void Renderer::processInput(GLFWwindow* window, float deltaTime) {
    // Process input
}

void Renderer::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Renderer::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    // Mouse callback code
}

void Renderer::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    // Scroll callback code
}