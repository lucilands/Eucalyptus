#include "matrix.h"



namespace Eucalyptus {
    namespace Math {
        Matrix2x2::Matrix2x2(float a11, float a12, float a21, float a22) {
            this->a11 = a11;
            this->a12 = a12;
            this->a21 = a21;
            this->a22 = a22;
        }
        Matrix2x2::Matrix2x2() {
            this->a11 = 0;
            this->a12 = 0;
            this->a21 = 0;
            this->a22 = 0;
        }

        Matrix2x2 Matrix2x2::multiply(Matrix2x2 a, Matrix2x2 b) {
            float a1 = a.a11 * b.a11 + a.a12 * b.a21;
            float b1 = a.a11 * b.a12 + a.a12 * b.a22;

            float c1 = a.a21 * b.a11 + a.a22 * b.a21;
            float d1 = a.a21 * b.a12 + a.a22 * b.a22;
            return Matrix2x2(a1, b1, c1, d1);
        }
    }
}