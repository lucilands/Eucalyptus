#pragma once

#include "api.h"

#include "math/transform.h"
#include "color/color.h"

#include <vector>


namespace Eucalyptus {
    class _EUCAPI Light {
    public:
        Math::Transform transform;

        Color light_color;
        float strengt;
    };
}