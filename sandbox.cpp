#include <Eucalyptus.h>



int main() {
    Eucalyptus::Init();
    Eucalyptus::Window window(Eucalyptus::Vector2u(1080, 720), "Demo window");

    Eucalyptus::Scene main_scene;
    Eucalyptus::Object cube = Eucalyptus::Object();
    Eucalyptus::Shader basic = Eucalyptus::Shader::FromFile("shader/vert.vs", "shader/frag.fs");

    cube.AddComponent<Eucalyptus::Mesh>(basic);
    cube.GetComponent<Eucalyptus::Mesh>()->verts = {-0.5f, -0.5f, 0.0f,
                                                     0.5f, -0.5f, 0.0f,
                                                     0.0f,  0.5f, 0.0f
    };

    main_scene.AddObject(&cube);

    main_scene.Awake();
    while (window.IsRunning()) {
        window.Clear(Eucalyptus::Colors::DarkGray);
        cube.GetComponent<Eucalyptus::Transform>()->Rotate(0.01, {0.0, 1.0, 1.0});
        main_scene.Update();
        window.Update();
    }

    Eucalyptus::Terminate();
    return 0;
}