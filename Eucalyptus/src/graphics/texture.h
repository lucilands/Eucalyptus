#pragma once
#include "api.h"




namespace Eucalyptus {
    // TODO: Fix issue with loading certain images as textures
    
    class _EUCAPI Texture {
    public:
        Texture(unsigned char *image_data, int width, int height);

        static Texture LoadFromFile(const char* path);

        void Bind();

    private:
        unsigned int m_gltexture;
    };
}