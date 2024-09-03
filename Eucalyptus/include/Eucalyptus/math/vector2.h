#pragma once


namespace Eucalyptus {
    template <typename T> class Vector2 {
        public:
            Vector2(T x, T y) {this->x = x; this->y = y;};
            Vector2() {x = 0; y = 0;}

            T x;
            T y;
    };

    typedef Vector2<int> Vector2i;
    typedef Vector2<float> Vector2f;
    typedef Vector2<unsigned int> Vector2u;
}