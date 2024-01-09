#pragma once
#include "api.h"
#include "math/vector.h"


#define __COLOR_TO_ARGS(arg) arg.r, arg.g, arg.b, arg.a

namespace Eucalyptus {
    class _EUCAPI Color {
    public:
        Color(float R, float G, float B, float A) {r = R; g = G; b = B; a = A;}
        float r, g, b, a;

        Math::Vector4f ToVector4f(){
            return Math::Vector4f(r, g, b, a);
        }
        Math::Vector4i ToVector4i(){
            return Math::Vector4i(r, g, b, a);
        }

        Math::Vector3f ToVector3f(){
            return Math::Vector3f(r, g, b);
        }
        Math::Vector3i ToVector3i(){
            return Math::Vector3i(r, g, b);
        }
        static const Color BLACK;
        static const Color WHITE;
        
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;

        static const Color DARK_GRAY;
        static const Color LIGHT_GRAY;
    };

     
}