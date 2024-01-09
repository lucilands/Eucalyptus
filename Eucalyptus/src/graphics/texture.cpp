#include "texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "internal.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


namespace Eucalyptus {
    Texture::Texture(unsigned char *image_data = (unsigned char*)"", int width = 1, int height = 1) {
        glGenTextures(1, &m_gltexture);
        glBindTexture(GL_TEXTURE_2D, m_gltexture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    Texture Texture::LoadFromFile(const char *path)
    {
        int width, height, nrChannels;

        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data == NULL) {
            _EUC_LOG_ERR("Could not load image");
        }

        return Texture(data, width, height);
    }

    void Texture::Bind() {
        glBindTexture(GL_TEXTURE_2D, m_gltexture);
    }
}