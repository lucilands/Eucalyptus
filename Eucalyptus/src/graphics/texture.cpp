#include <Eucalyptus/graphics/texture.h>

#include <clog.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



namespace Eucalyptus {
    Texture::Texture(const char *path) {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 3);

        if (data == NULL) {
            clog(CLOG_ERROR, "Failed to load texture %s", path);
        }

        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
    void Texture::Use() {
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }
}