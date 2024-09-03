#pragma once
#include "../vendor/glm/glm/glm.hpp"


namespace Eucalyptus {
    template <typename T> class Vector3 {
        public:
            Vector3(T x, T y, T z) {this->x = x; this->y = y; this->z = z;};
            Vector3() {x = 0; y = 0; z = 0;}

            glm::vec3 asGLM() {
                return glm::vec3(x, y, z);
            }

            static Vector3 fromGLM(glm::vec3 v) {
                return Vector3(v.x, v.y, v.z);
            }

            T x;
            T y;
            T z;
    };

    typedef Vector3<int> Vector3i;
    typedef Vector3<float> Vector3f;
    typedef Vector3<unsigned int> Vector3u;
}