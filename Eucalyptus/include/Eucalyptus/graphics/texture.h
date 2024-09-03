#pragma once


#include "../vendor/glad/include/glad/glad.h"


namespace Eucalyptus {
    class Texture {
        public:
            Texture(const char *path);
            Texture(const unsigned char *data);

            void Use() {glBindTexture(GL_TEXTURE_2D, m_ID);}

        private:
            unsigned int m_ID;
    };
}