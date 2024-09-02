#include <Eucalyptus/ecs/scene.h>
#include <Eucalyptus/ecs/object.h>



namespace Eucalyptus {
    void Scene::Awake() {
        for (Object *o : m_objects) {
            o->Awake();
        }
    }

    void Scene::Update() {
        for (Object *o : m_objects) {
            if (o->enabled) o->Update();
        }
    }

    void Scene::AddObject(Object *obj) {
        m_objects.push_back(obj);
    }
}