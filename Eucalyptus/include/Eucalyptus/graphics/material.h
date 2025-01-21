#pragma once

#include "shader.h"
#include "texture.h"


namespace Eucalyptus {
    class Material {
        public:
            Material(Shader sh, Texture tex) : m_shader(sh), m_texture(tex) {}

            void Use() {
                m_texture.Use();
                m_shader.Use();
            }

            Shader GetShader() {return m_shader;}
        private:
            Shader m_shader;
            Texture m_texture;
    };
}