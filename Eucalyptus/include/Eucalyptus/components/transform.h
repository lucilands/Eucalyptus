#pragma once

#include "../math/vector3.h"

#include <typeinfo>

#include "../ecs/object.h"
#include "../vendor/glm/glm/glm.hpp"
#include "../vendor/glm/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/glm/gtc/type_ptr.hpp"

namespace Eucalyptus {
    class Transform : public Component {
        public:
            Transform(Object *_) : Component(_) {}

            void Awake() {}
            void Update() {}

            void Translate(Vector3f t);
            void Rotate(float angle, Vector3f r);

            void Scale(Vector3f t);
            void Scale(float t);

            glm::mat4 _get_transform() {return m_transform;}
        private:
            glm::mat4 m_transform = glm::mat4(1.0f);
    };
}