#pragma once
#include "../graphics/shader.h"
#include "../ecs/object.h"

#include "../math/vector4.h"

#include "panel.h"




namespace Eucalyptus {
    class UI_Renderer : public Component {
        public:
            UI_Renderer(Object *_);
            void Update();

            Vector4f color;
            float radius;
        private:
            unsigned int m_VAO;
            Shader m_shader;
            glm::mat4 m_projection;
    };
}