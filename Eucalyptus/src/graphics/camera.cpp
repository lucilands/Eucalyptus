#include <Eucalyptus/graphics/camera.h>



namespace Eucalyptus {
    glm::mat4 Camera::GetViewMatrix() {
        return glm::lookAt(vec3_asGLM(position), vec3_asGLM(position) + vec3_asGLM(front), vec3_asGLM(up));
    }

    glm::mat4 Camera::GetProjectionMatrix() {
        return glm::perspective(glm::radians(fov), res.x / res.y, 0.1f, 100.0f);
    }

    void Camera::Update() {
        glm::vec3 _front;
        _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        _front.y = sin(glm::radians(pitch));
        _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        front = vec3_fromGLM<float>(glm::normalize(vec3_asGLM(front)));
        right = vec3_fromGLM<float>(glm::normalize(glm::cross(vec3_asGLM(front), vec3_asGLM(worldUp))));
        up = vec3_fromGLM<float>(glm::normalize(glm::cross(vec3_asGLM(right), vec3_asGLM(front))));
    }
}