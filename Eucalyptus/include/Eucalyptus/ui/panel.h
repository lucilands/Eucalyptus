#pragma once
#include "../ecs/object.h"
#include "../math/vector2.h"
#include "../math/vector4.h"



namespace Eucalyptus {
    class Panel : public Object {
        public:
            Panel(Vector2f size);
            Panel(Vector2f size, Vector4f color);
            Panel(Vector2f size, Vector2f position);
            Panel(Vector2f size, float rotation);
            Panel(Vector2f size, Vector2f position, float rotation);
            Panel(Vector2f size, Vector2f position, float rotation, Vector4f color);

            template <class T> void AddComponent_P() {
                static_assert(std::is_base_of<Component, T>::value, "AddComponent needs a Component");
                m_components.push_back(std::make_unique<T>(T(this)));
            }

            template <class T, typename ...Args> void AddComponent_P(Args &&...args) {
                static_assert(std::is_base_of<Component, T>::value, "AddComponent needs a Component");
                m_components.push_back(std::make_unique<T>(T(this, std::forward<Args>(args)...)));
            }
        private:
            void m_init(Vector2f size, Vector2f position, float rotation, Vector4f color);
    };
}