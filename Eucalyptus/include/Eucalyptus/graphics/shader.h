#pragma once

#include "../vendor/glm/glm/glm.hpp"
#include "Eucalyptus/math/vector3.h"

#include "../vendor/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

namespace Eucalyptus {
    class Shader {
        public:
            Shader(const char *vertex_src, const char *fragment_src);
            static Shader FromFile(const char *vert_path, const char *frag_path);

            void Use();

            void SetMat4(const char *name, const glm::mat4 mat4) {
                glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, &mat4[0][0]);
            }

            void SetFloat(const char *name, const float val) {
                glUniform1f(glGetUniformLocation(m_ID, name), val);
            }

            void SetVec3(const char *name, const Vector3f val) {
                glUniform3f(glGetUniformLocation(m_ID, name), val.x, val.y, val.z);
            }

        private:
            unsigned int m_ID;
    };
}