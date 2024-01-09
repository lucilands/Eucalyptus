#pragma once

#include <string>

#include "api.h"
#define TEMPL template <typename T>


namespace Eucalyptus{
    namespace Math{
        TEMPL class _EUCAPI Vector2{
        public:
            Vector2(T x, T y) {this->x = x; this->y = y;};
            T x;
            T y;
            Vector2() = default;

            Vector2<T> operator+(const Vector2<T> b){
                Vector2<T> res;
                res.x += b.x;
                res.y += b.y;
                return res;
            }
            Vector2<T> operator+(const T b){
                Vector2<T> res;
                res.x += b;
                res.y += b;
                return res;
            }
            
            Vector2<T> operator-(const Vector2<T> b){
                Vector2<T> res;
                res.x -= b.x;
                res.y -= b.y;
                return res;
            }
            Vector2<T> operator-(const T b){
                Vector2<T> res;
                res.x -= b;
                res.y -= b;
                return res;
            }

            Vector2<T> operator*(const Vector2<T> b){
                Vector2<T> res;
                res.x *= b.x;
                res.y *= b.y;
                return res;
            }
            Vector2<T> operator*(const T b){
                Vector2<T> res;
                res.x *= b;
                res.y *= b;
                return res;
            }

            Vector2<T> operator/(const Vector2<T> b){
                Vector2<T> res;
                res.x /= b.x;
                res.y /= b.y;
                return res;
            }
            Vector2<T> operator/(const T b){
                Vector2<T> res;
                res.x /= b;
                res.y /= b;
                return res;
            }

            
        };
    TEMPL class _EUCAPI Vector3{
        public:
            Vector3(T x, T y, T z) {this->x = x; this->y = y; this->z = z;};
            Vector3() = default;
            T x;
            T y;
            T z;

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
        };
    TEMPL class _EUCAPI Vector4{
        public:
            Vector4(T x, T y, T z, T w) {this->x = x; this->y = y, this->z = z; this->w = w;};
            Vector4() = default;
            T x;
            T y;
            T z;
            T w;

            Vector4<T> operator+(const Vector4<T> b){
                Vector4<T> res;
                res.x += b.x;
                res.y += b.y;
                res.z += b.z;
                res.w += b.w;
                return res;
            }
            Vector4<T> operator+(const T b){
                Vector4<T> res;
                res.x += b;
                res.y += b;
                res.z += b;
                res.w += b;
                return res;
            }
            
            Vector4<T> operator-(const Vector4<T> b){
                Vector4<T> res;
                res.x -= b.x;
                res.y -= b.y;
                res.z -= b.z;
                res.w -= b.w;
                return res;
            }
            Vector4<T> operator-(const T b){
                Vector4<T> res;
                res.x -= b;
                res.y -= b;
                res.z -= b;
                res.w -= b;
                return res;
            }

            Vector4<T> operator*(const Vector4<T> b){
                Vector4<T> res;
                res.x *= b.x;
                res.y *= b.y;
                res.z *= b.z;
                res.w *= b.w;
                return res;
            }
            Vector4<T> operator*(const T b){
                Vector4<T> res;
                res.x *= b;
                res.y *= b;
                res.z *= b;
                res.w *= b;
                return res;
            }

            Vector4<T> operator/(const Vector4<T> b){
                Vector4<T> res;
                res.x /= b.x;
                res.y /= b.y;
                res.z /= b.z;
                res.w /= b.w;
                return res;
            }
            Vector4<T> operator/(const T b){
                Vector4<T> res;
                res.x /= b;
                res.y /= b;
                res.z /= b;
                res.w /= b;
                return res;
            }

            
        };

        using Vector2i = Vector2<int>;
        using Vector2f = Vector2<float>;
        using Vector2d = Vector2<double>;

        using Vector3i = Vector3<int>;
        using Vector3f = Vector3<float>;
        using Vector3d = Vector3<double>;

        using Vector4i = Vector4<int>;
        using Vector4f = Vector4<float>;
        using Vector4d = Vector4<double>;
    }
}