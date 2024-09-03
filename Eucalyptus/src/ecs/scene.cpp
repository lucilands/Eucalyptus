#include <Eucalyptus/ecs/scene.h>
#include <Eucalyptus/ecs/object.h>

#include <Eucalyptus/components/model_renderer.h>


namespace Eucalyptus {
    void Scene::Awake() {
        m_camera.res = {1080.0f, 720.0f};
        for (Object *o : m_objects) {
            o->Awake();
        }
    }

    void Scene::Update() {
        m_camera.Update();
        for (Object *o : m_objects) {
            if (o->enabled) o->Update();
            if (o->HasComponent<ModelRenderer>()) {
                o->GetComponent<ModelRenderer>()->GetShader().SetMat4("_view", m_camera.GetViewMatrix());
                o->GetComponent<ModelRenderer>()->GetShader().SetMat4("_projection", m_camera.GetProjectionMatrix());
            }
        }
    }

    void Scene::AddObject(Object *obj) {
        m_objects.push_back(obj);
    }
}