#pragma once


namespace Eucalyptus {
    template <typename T> struct Vector2 {
        public:
            T x;
            T y;
    };

    typedef Vector2<int> Vector2i;
    typedef Vector2<float> Vector2f;
    typedef Vector2<unsigned int> Vector2u;
}