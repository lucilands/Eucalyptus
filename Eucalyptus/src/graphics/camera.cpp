#include <Eucalyptus/graphics/camera.h>



namespace Eucalyptus {
    glm::mat4 Camera::GetViewMatrix() {
        return glm::lookAt(position.asGLM(), position.asGLM() + front.asGLM(), up.asGLM());
    }

    glm::mat4 Camera::GetProjectionMatrix() {
        return glm::perspective(glm::radians(fov), res.x / res.y, 0.1f, 100.0f);
    }

    void Camera::Update() {
        glm::vec3 _front;
        _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        _front.y = sin(glm::radians(pitch));
        _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        front = Vector3f::fromGLM(glm::normalize(front.asGLM()));
        right = Vector3f::fromGLM(glm::normalize(glm::cross(front.asGLM(), worldUp.asGLM())));
        up = Vector3f::fromGLM(glm::normalize(glm::cross(right.asGLM(), front.asGLM())));
    }
}