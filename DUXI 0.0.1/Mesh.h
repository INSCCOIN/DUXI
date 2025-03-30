#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    GLuint VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    void Draw();

private:
    GLuint VBO, EBO;
    void setupMesh();
};

#endif // MESH_H