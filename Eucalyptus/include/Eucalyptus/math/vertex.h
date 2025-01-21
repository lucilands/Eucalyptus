#pragma once


#include "vector3.h"
#include "vector2.h"


namespace Eucalyptus {
    struct Vertex {
        Vector3f position;
        Vector2f tex_coord;
        Vector3f normal;
    };
}