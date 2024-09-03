#include <Eucalyptus/ecs/object.h>

#include <clog.h>
#include <typeinfo>



namespace Eucalyptus {
    void Object::Awake() {
        for (auto& c : m_components) {
            c->Awake();
        }
    }

    void Object::Update() {
        for (auto& c : m_components) {
            c->Update();
        }
    }
}