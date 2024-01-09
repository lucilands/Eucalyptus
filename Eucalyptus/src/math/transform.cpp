#include "transform.h"



#define _GLM_VEC3(vec) glm::vec3(vec.x, vec.y, vec.z) 


namespace Eucalyptus {
    namespace Math {
        Transform::Transform() {
            m_transform = glm::mat4(1.0f);
            m_view = glm::mat4(1.0f);
            m_projection = glm::mat4(1.0f);

            m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -3.0f));
        }
        void Transform::Translate(Vector3f translate_by) {
            m_transform = glm::translate(m_transform, _GLM_VEC3(translate_by));
        }
        void Transform::Rotate(float degrees, Vector3f axis) {
            m_transform = glm::rotate(m_transform, glm::radians(degrees), _GLM_VEC3(axis));
        }
        void Transform::Scale(Vector3f scale_by) {
            m_transform = glm::scale(m_transform, _GLM_VEC3(scale_by));
        }
    }
}
