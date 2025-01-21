#pragma once

#include "../ecs/object.h"

#include "../graphics/material.h"
#include "../graphics/shader.h"
#include "../graphics/model.h"
#include "../graphics/mesh.h"



namespace Eucalyptus {
    class ModelRenderer : public Component {
        public:
            ModelRenderer(Object *_, Model md);

            void Awake();
            void Update();
        
            Shader GetShader() {return m_model.GetMaterial().GetShader();}

            std::vector<float> verts;
        private:

            unsigned int m_VBO;
            unsigned int m_VAO;
            unsigned int m_EBO;

            Model m_model;
    };
}