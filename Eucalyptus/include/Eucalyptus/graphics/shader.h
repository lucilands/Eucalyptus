#pragma once

#include "../vendor/glm/glm/glm.hpp"
#include "Eucalyptus/math/vector3.h"


namespace Eucalyptus {
    class Shader {
        public:
            Shader(const char *vertex_src, const char *fragment_src);
            static Shader FromFile(const char *vert_path, const char *frag_path);

            void Use();

            void SetMat4(const char *name, const glm::mat4 mat4);
            void SetFloat(const char *name, const float val);
            void SetVec3(const char *name, const Vector3f val);

        private:
            unsigned int m_ID;
    };
}