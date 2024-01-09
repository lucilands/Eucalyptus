#include "vector.h"





namespace Eucalyptus{
    namespace Math {
         Vector3<T> operator+(const Vector3<T> b){
                Vector3<T> res;
                res.x += b.x;
                res.y += b.y;
                res.z += b.z;
                return res;
            }
            Vector3<T> operator+(const T b){
                Vector3<T> res;
                res.x += b;
                res.y += b;
                res.z += b;
                return res;
            }
            
            Vector3<T> operator-(const Vector3<T> b){
                Vector3<T> res;
                res.x -= b.x;
                res.y -= b.y;
                res.z -= b.z;
                return res;
            }
            Vector3<T> operator-(const T b){
                Vector3<T> res;
                res.x -= b;
                res.y -= b;
                res.z -= b;
                return res;
            }

            Vector3<T> operator*(const Vector3<T> b){
                Vector3<T> res;
                res.x *= b.x;
                res.y *= b.y;
                res.z *= b.z;
                return res;
            }
            Vector3<T> operator*(const T b){
                Vector3<T> res;
                res.x *= b;
                res.y *= b;
                res.z *= b;
                return res;
            }

            Vector3<T> operator/(const Vector3<T> b){
                Vector3<T> res;
                res.x /= b.x;
                res.y /= b.y;
                res.z /= b.z;
                return res;
            }
            Vector3<T> operator/(const T b){
                Vector3<T> res;
                res.x /= b;
                res.y /= b;
                res.z /= b;
                return res;
            }
    }
}