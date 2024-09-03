#pragma once
#include "../ecs/component.h"
#include "../graphics/shader.h"
#include "../graphics/model.h"



namespace Eucalyptus {
    class Mesh : public Component {
        public:
            Mesh(Object *_, Shader sh, Model md);

            void Awake();
            void Update();
        
            Shader GetShader() {return m_shader;}

            std::vector<float> verts;
        private:

            unsigned int m_VBO;
            unsigned int m_VAO;
            unsigned int m_EBO;

            Shader m_shader;
            Model m_model;
    };
}