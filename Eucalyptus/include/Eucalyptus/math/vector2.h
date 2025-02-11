#pragma once


namespace Eucalyptus {
    template <typename T> struct Vector2 {
        public:
            Vector2() {x = 0; y = 0;}
            Vector2(T X, T Y) {x = X; y = Y;}
            T x;
            T y;
    };

    typedef Vector2<int> Vector2i;
    typedef Vector2<float> Vector2f;
    typedef Vector2<unsigned int> Vector2u;
}