#pragma once


#include "../graphics/material.h"
#include "../graphics/shader.h"
#include "../graphics/model.h"



namespace Eucalyptus {
    class Mesh : public Component {
        public:
            Mesh(Object *_, Material mat, Model md);

            void Awake();
            void Update();
        
            Shader GetShader() {return m_material.GetShader();}

            std::vector<float> verts;
        private:

            unsigned int m_VBO;
            unsigned int m_VAO;
            unsigned int m_EBO;

            Material m_material;
            Model m_model;
    };
}