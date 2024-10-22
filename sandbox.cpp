#include <Eucalyptus.h>



float rotation_speed = 10.0f;

class Rotate : public Eucalyptus::Component {
    public:
        Rotate(Eucalyptus::Object *_, float speed = 10.0f, Eucalyptus::Vector3f direction = {1.0f,1.0f,1.0f}) : Component(_), m_speed(speed), m_direction(direction) {}
        void Update() {
            m_parent->GetComponent<Eucalyptus::Transform>()->Rotate(m_speed * Eucalyptus::Window::GetDeltaTime(), m_direction);
        }
    private:
        float m_speed;
        Eucalyptus::Vector3f m_direction;
};

int main() {
    Eucalyptus::Init();
    Eucalyptus::Window window({1080, 720}, "Demo window");

    Eucalyptus::Scene main_scene;
    Eucalyptus::Object monkey;
    Eucalyptus::Object sphere;

    Eucalyptus::Shader basic_shader = Eucalyptus::Shader::FromFile("assets/shader/vert.vs", "assets/shader/frag.fs");
    Eucalyptus::Material basic(basic_shader, Eucalyptus::Texture("assets/texture/brick.jpg"));

    Eucalyptus::Model monkey_model(basic, Eucalyptus::LoadGLBmesh("assets/models/monkey.glb"));
    Eucalyptus::Model sphere_model(basic, Eucalyptus::LoadGLBmesh("assets/models/sphere.glb"));

    monkey.AddComponent<Eucalyptus::ModelRenderer>(monkey_model);
    sphere.AddComponent<Eucalyptus::ModelRenderer>(sphere_model);

    monkey.AddComponent<Rotate>(rotation_speed, (Eucalyptus::Vector3f) {1.0f, 1.0f, 1.0f});
    sphere.AddComponent<Rotate>(rotation_speed, (Eucalyptus::Vector3f) {-1.0f, -1.0f, -1.0f});

    main_scene.AddObject(&monkey);
    main_scene.AddObject(&sphere);
    main_scene.GetCamera()->position = {0.0f, 0.0f, 10.0f};

    sphere.GetComponent<Eucalyptus::Transform>()->Translate({3.0f, 0.0f, 0.0f});

    main_scene.Awake();
    while (window.IsRunning()) {
        window.Clear(Eucalyptus::Colors::DarkGray);
        
        main_scene.Update();
        window.Update();
    }

    Eucalyptus::Terminate();
    return 0;
}