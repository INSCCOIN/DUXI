#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialize();
    void Run();
    void Shutdown();

private:
    Window window;
    Shader* shader;
    Mesh* mesh;
    Camera* camera;

    float lastX, lastY;
    bool firstMouse;

    void processInput(GLFWwindow* window, float deltaTime);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif // RENDERER_H