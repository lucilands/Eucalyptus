#pragma once
#include "../vendor/glm/glm/glm.hpp"
#include "vector3.h"

namespace Eucalyptus {
    template <typename T> struct Vector4 {
        public:
            Vector4() {x = 0; y = 0; z = 0; w = 0;}
            Vector4(T X, T Y, T Z, T W) {x = X; y = Y; z = Z; w = W;}
            T x;
            T y;
            T z;
            T w;

            Vector3<T> xyz() {return Vector3<T>(x, y, z);}
    };

    typedef Vector4<int> Vector4i;
    typedef Vector4<float> Vector4f;
    typedef Vector4<unsigned int> Vector4u;
}