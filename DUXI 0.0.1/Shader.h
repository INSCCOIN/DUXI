#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader();
    ~Shader();
    void load(const char* vertexPath, const char* fragmentPath);
    void use();
    GLuint getProgramID() const;

private:
    GLuint programID;
    std::string readFile(const char* filePath);
    GLuint compileShader(const char* source, GLenum shaderType);
};

#endif // SHADER_H