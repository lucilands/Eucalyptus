#pragma once

#include "api.h"
#include "texture.h"
#include "color/color.h"




namespace Eucalyptus {
    struct _EUCAPI Material {
        Material();
        Texture texture;
        Color color;
    };
}