#include <Eucalyptus.h>



float rotation_speed = 10.0f;
float camera_speed = 10.0f;

class Rotate : public Eucalyptus::Component {
    public:
        Rotate(Eucalyptus::Object *_, float speed = 10.0f, Eucalyptus::Vector3f direction = {1.0f,1.0f,1.0f}) : Component(_), m_speed(speed), m_direction(direction) {
            RequireComponent<Eucalyptus::Transform>();
        }
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
    Eucalyptus::Object cube;

    Eucalyptus::Shader basic_shader = Eucalyptus::Shader::FromFile("assets/shader/default.vert", "assets/shader/default.frag");
    Eucalyptus::Material basic(basic_shader, Eucalyptus::Texture("assets/texture/brick.jpg"));
    Eucalyptus::Material basic_monkey(basic_shader, Eucalyptus::Texture("assets/texture/monkey.png"));

    Eucalyptus::Model monkey_model(basic_monkey, Eucalyptus::LoadGLBmesh("assets/models/monkey.glb"));
    Eucalyptus::Model sphere_model(basic, Eucalyptus::LoadGLBmesh("assets/models/sphere.glb"));
    Eucalyptus::Model cube_model(basic, Eucalyptus::Prefabs::Cube);

    monkey.AddComponent<Eucalyptus::ModelRenderer>(monkey_model);
    sphere.AddComponent<Eucalyptus::ModelRenderer>(sphere_model);
    cube.AddComponent<Eucalyptus::ModelRenderer>(cube_model);

    monkey.AddComponent<Rotate>(rotation_speed, (Eucalyptus::Vector3f) {1.0f, 1.0f, 1.0f});
    sphere.AddComponent<Rotate>(rotation_speed, (Eucalyptus::Vector3f) {1.0f, -1.0f, -1.0f});
    cube.AddComponent<Rotate>(rotation_speed, (Eucalyptus::Vector3f) {1.0f, 1.0f, -1.0f});

    main_scene.AddObject(&monkey);
    main_scene.AddObject(&sphere);
    main_scene.AddObject(&cube);

    main_scene.GetCamera()->position = {0.0f, 0.0f, 10.0f};

    sphere.GetComponent<Eucalyptus::Transform>()->Translate({3.0f, 0.0f, 0.0f});
    cube.GetComponent<Eucalyptus::Transform>()->Translate({-3.0f, 0.0f, 0.0f});

    main_scene.Awake();
    while (window.IsRunning()) {
        window.Clear(Eucalyptus::Colors::DarkGray);

        Eucalyptus::Vector3f cam_pos = main_scene.GetCamera()->position;
        main_scene.GetCamera()->position = {cam_pos.x + (camera_speed * (-window.input.held_keys['a'] + window.input.held_keys['d']) * window.GetDeltaTime()),
                                            cam_pos.y + (camera_speed * (-window.input.IsKeyHeld(Eucalyptus::Input::KeyCode::SHIFT) + window.input.IsKeyHeld(Eucalyptus::Input::KeyCode::CONTROL)) * window.GetDeltaTime()),
                                            cam_pos.z + (camera_speed * (-window.input.held_keys['w'] + window.input.held_keys['s']) * window.GetDeltaTime())};

        if (window.input.IsKeyPressed(Eucalyptus::Input::KeyCode::NUMPAD_ADD)) {
            camera_speed+=1.0f;
            printf("camera_speed: %f\r", camera_speed);
        }
        if (window.input.IsKeyPressed(Eucalyptus::Input::KeyCode::NUMPAD_SUBTRACT)) {
            camera_speed-=1.0f;
            printf("camera_speed: %f\r", camera_speed);
        }

        main_scene.Update();
        window.Update();
    }

    Eucalyptus::Terminate();
    return 0;
}