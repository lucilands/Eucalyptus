#pragma once
#include "../ecs/object.h"
#include "../math/vector2.h"




namespace Eucalyptus {
    class Transform2D : public Component {
        public:
            Transform2D(Object *_) : Component(_) {}

            Vector2f size = {100.0f, 100.0f};
            Vector2f position = {0.0f, 0.0f};
            float rotation = 0.0f;
    };
}