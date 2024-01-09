#pragma once
#include "api.h"






// TODO: Use ints instead of floats for better accuracy

namespace Eucalyptus {
    namespace Math {
        class _EUCAPI Matrix2x2 {
        public:
            float a11, a12,
                  a21, a22;
            
            Matrix2x2(float a11, float a12, float a21, float a22);
            Matrix2x2();

            static Matrix2x2 multiply(Matrix2x2 a, Matrix2x2 b);
        };
    }
}