#include <Eucalyptus.h>




int main() {
    Eucalyptus::Init();
    Eucalyptus::Window window({1080, 720}, "Demo window");

    Eucalyptus::Scene main_scene;
    Eucalyptus::Object cube;

    Eucalyptus::Shader basic_shader = Eucalyptus::Shader::FromFile("assets/shader/vert.vs", "assets/shader/frag.fs");
    Eucalyptus::Material basic(basic_shader, Eucalyptus::Texture("assets/texture/brick.jpg"));

    Eucalyptus::Model model(basic, Eucalyptus::LoadGLBmesh("assets/models/sphere.glb"));

    cube.AddComponent<Eucalyptus::ModelRenderer>(model);

    main_scene.AddObject(&cube);

    main_scene.Awake();
    while (window.IsRunning()) {
        window.Clear(Eucalyptus::Colors::DarkGray);

        cube.GetComponent<Eucalyptus::Transform>()->Rotate(10.0f * window.delta_time, {1.0, 1.0, 0.0});
        
        main_scene.Update();
        window.Update();
    }

    Eucalyptus::Terminate();
    return 0;
}