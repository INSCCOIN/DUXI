#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window {
public:
    Window();
    ~Window();

    bool Create();
    void Destroy();

    GLFWwindow* GetGLFWwindow() const;
    int GetWidth() const;
    int GetHeight() const;

private:
    GLFWwindow* window;
    int width;
    int height;
};

#endif // WINDOW_H