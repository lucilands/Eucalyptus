#pragma once


#include "../math/vector3.h"
#include "../math/vector2.h"

#include "../vendor/glm/glm/glm.hpp"
#include "../vendor/glm/glm/gtc/matrix_transform.hpp"




namespace Eucalyptus {
    class Camera {
        public:
            Camera() {};

            glm::mat4 GetViewMatrix();
            glm::mat4 GetProjectionMatrix();

            void Update();

            Vector3f position = {0.0f, 0.0f, 3.0f};
            Vector3f front = {0.0f, 0.0f, -1.0f};
            Vector3f up = {0.0f, 1.0f, 0.0f};
            Vector3f right;
            Vector3f worldUp = up;

            Vector2f res;

            float yaw = -90.0f;
            float pitch;
            float fov = 45;
    };
}