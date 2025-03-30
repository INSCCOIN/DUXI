#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    enum class Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    void processKeyboard(Movement direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    void processMouseScroll(float yOffset);

private:
    void updateCameraVectors();
};

#endif