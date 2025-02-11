#include <Eucalyptus/ecs/object.h>
#include <Eucalyptus/ecs/scene.h>

#include <clog.h>
#include <typeinfo>



namespace Eucalyptus {
    Object::Object() {
        default_scene->AddObject(this);
    }
    Object::Object(Scene scene) {
        scene.AddObject(this);
    }

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