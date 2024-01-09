#include "material.h"
#include <stdio.h>




namespace Eucalyptus {
    
    Material::Material() : texture(Texture(reinterpret_cast<unsigned char*>(*""), 1, 1)), color(Color::WHITE) {

    }
}