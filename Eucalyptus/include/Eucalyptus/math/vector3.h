#pragma once


namespace Eucalyptus {
    template <typename T> class Vector3 {
        public:
            Vector3(T x, T y, T z) {this->x = x; this->y = y; this->z = z;};

            T x;
            T y;
            T z;
    };

    typedef Vector3<int> Vector3i;
    typedef Vector3<float> Vector3f;
    typedef Vector3<unsigned int> Vector3u;
}