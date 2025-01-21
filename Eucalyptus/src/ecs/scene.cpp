#include <Eucalyptus/ecs/scene.h>
#include <Eucalyptus/ecs/object.h>

#include <Eucalyptus/components/model_renderer.h>
#include <Eucalyptus/window.h>


namespace Eucalyptus {
    void Scene::Awake() {
        for (Object *o : m_objects) {
            o->Awake();
        }
    }

    void Scene::Update() {
        m_camera.Update();
        m_camera.res = {static_cast<float>(Eucalyptus::window->size.x), static_cast<float>(Eucalyptus::window->size.y)};
        for (Object *o : m_objects) {
            if (o->enabled) o->Update();
            if (o->HasComponent<ModelRenderer>()) {
                o->GetComponent<ModelRenderer>()->GetShader().SetMat4("_view", m_camera.GetViewMatrix());
                o->GetComponent<ModelRenderer>()->GetShader().SetMat4("_projection", m_camera.GetProjectionMatrix());
                o->GetComponent<ModelRenderer>()->GetShader().SetVec3("_viewPos", m_camera.position);
            }
        }
    }

    void Scene::AddObject(Object *obj) {
        m_objects.push_back(obj);
    }
}