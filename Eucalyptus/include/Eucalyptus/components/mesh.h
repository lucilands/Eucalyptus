#pragma once
#include "../ecs/component.h"
#include "../graphics/shader.h"



namespace Eucalyptus {
    class Mesh : public Component {
        public:
            Mesh(Object *_, Shader sh);

            void Awake();
            void Update();
        
            Shader GetShader() {return m_shader;}

            std::vector<float> verts;
        private:

            unsigned int m_VBO;
            unsigned int m_VAO;

            Shader m_shader;
    };
}