#include <Eucalyptus/components/transform.h>

namespace Eucalyptus {
    void Transform::Translate(Vector3f t) {
        m_transform = glm::translate(m_transform, glm::vec3(t.x, t.y, t.z));
    }

    void Transform::Rotate(float angle, Vector3f r) {
        m_transform = glm::rotate(m_transform, glm::radians(angle), glm::vec3(r.x, r.y, r.z));
    }

    void Transform::Scale(Vector3f t) {
        m_transform = glm::scale(m_transform, glm::vec3(t.x, t.y, t.z));
    }
    void Transform::Scale(float t) {
        m_transform = glm::scale(m_transform, glm::vec3(t, t, t));
    }
}