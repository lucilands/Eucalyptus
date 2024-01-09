#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window/window.h"

#include "api.h"
#include "vector.h"



namespace Eucalyptus {
    namespace Math {
        class _EUCAPI Transform {
        public:
            Transform();

            void Translate(Vector3f translate_by);
            void Rotate(float degrees, Vector3f axis);
            void Scale(Vector3f scale_by);
            
            glm::mat4 GetTransform() { return m_transform; }
            glm::mat4 GetProjection(Window& window) { 
                m_projection = glm::perspective(glm::radians(45.0f), (float)window.GetSize().x / (float)window.GetSize().y, 0.1f, 100.0f);
                return m_projection; 
            }
            glm::mat4 GetView() { 
                return m_view; 
            }
        private:
            glm::mat4 m_transform;
            glm::mat4 m_projection;
            glm::mat4 m_view;
        };
    }
}