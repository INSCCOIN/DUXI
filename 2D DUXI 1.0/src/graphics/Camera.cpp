#include "Camera.h"

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch)
    : position(startPosition), worldUp(startUp), yaw(startYaw), pitch(startPitch),
      movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(45.0f) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(zoom), aspectRatio, 0.1f, 100.0f);
}

void Camera::processKeyboard(Movement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (direction == Movement::FORWARD)
        position += front * velocity;
    if (direction == Movement::BACKWARD)
        position -= front * velocity;
    if (direction == Movement::LEFT)
        position -= right * velocity;
    if (direction == Movement::RIGHT)
        position += right * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset) {
    zoom -= yOffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}