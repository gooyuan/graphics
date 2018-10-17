//
// Created by Sophimp on 2018/10/17.
//

#ifndef CLIONOPENGL_CAMERA_H
#define CLIONOPENGL_CAMERA_H

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

enum CAMERA_DIRECTION {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera {
public:
    // camera attribute
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler angle
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH)
            : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Position = position;
        Up = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
            : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Position = glm::vec3(posX, posY, posZ);
        Up = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void ProcessKeyBoard(CAMERA_DIRECTION direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;
        switch (direction) {
            case FORWARD:
                Position += Front * velocity;
                break;
            case BACKWARD:
                Position -= Front * velocity;
                break;
            case RIGHT:
                Position += Right * velocity;
                break;
            case LEFT:
                Position -= Right * velocity;
                break;
        }
    }

    void ProcessMouseMovement(bool constrainPitch, float xoffset, float yoffset) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (constrainPitch) {
            if (Pitch > 89.0f) Pitch = 89.0f;
            if (Pitch < -89.0f) Pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void ProcessMouseScroll(int direction) {
        if (direction > 0) {
            Zoom += 1.0f;
        } else {
            Zoom -= 1.0f;
        }
        if (Zoom > 60.0f) Zoom = 60.0f;
        if (Zoom < 1.0f) Zoom = 1.0f;
    }

private:
    void updateCameraVectors() {
        glm::vec3 front;
        front.x = static_cast<float>(cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)));
        front.y = static_cast<float>(sin(glm::radians(Pitch)));
        front.z = static_cast<float>(sin(glm::radians(Yaw)) * cos(glm::radians(Pitch)));
        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Front, Right));
    }
};


#endif //CLIONOPENGL_CAMERA_H
