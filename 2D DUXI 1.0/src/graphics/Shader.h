#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp> // For glm::vec3, glm::vec4, glm::mat4

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader(); // Destructor to clean up resources

    void use();

    // Uniform setters
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::vec4& value);
    void setUniform(const std::string& name, const glm::mat4& value);

private:
    void checkCompileErrors(unsigned int shader, const std::string& type);
};

#endif