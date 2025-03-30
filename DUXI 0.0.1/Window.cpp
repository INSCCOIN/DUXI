#include "Window.h"
#include <iostream>

Window::Window() : window(nullptr), width(800), height(600) {
    // Constructor
}

Window::~Window() {
    Destroy();
}

bool Window::Create() {
    std::cout << "Creating Window..." << std::endl;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    window = glfwCreateWindow(width, height, "DUXI Renderer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    return true;
}

void Window::Destroy() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

GLFWwindow* Window::GetGLFWwindow() const {
    return window;
}

int Window::GetWidth() const {
    return width;
}

int Window::GetHeight() const {
    return height;
}