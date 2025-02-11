#pragma once
#include "../vendor/glm/glm/glm.hpp"


namespace Eucalyptus {
    template <typename T> struct Vector3 {
        public:
            Vector3(T x, T y, T z) {this->x = x; this->y = y; this->z = z;}
            T x;
            T y;
            T z;
    };

    typedef Vector3<int> Vector3i;
    typedef Vector3<float> Vector3f;
    typedef Vector3<unsigned int> Vector3u;

    template <typename T> glm::vec3 vec3_asGLM(Vector3<T> v) {
        return glm::vec3(v.x, v.y, v.z);
    }

    template <typename T> Vector3<T> vec3_fromGLM(glm::vec3 v) {
            return  {v.x, v.y, v.z};
    }
}