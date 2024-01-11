#include <Eucalyptus.h> 





int main(){
    Eucalyptus::Init();
    Eucalyptus::Window window(Eucalyptus::Math::Vector2i(1080, 720));
    window.InitWindow();

    //Eucalyptus::Shader shader = Eucalyptus::Shader::LoadFromFile(".\\shaders\\vertex.vs", ".\\shaders\\fragment.fs");
    Eucalyptus::Mesh tree = Eucalyptus::LoadMeshFromOBJ("models/tree-tex.obj");

    Eucalyptus::AudioClip audio("sound/Juhani Junkala [Retro Game Music Pack] Level 1.wav");

    Eucalyptus::MeshRenderer renderer(tree, Eucalyptus::Shader::Lit());

    renderer.transform.Scale({0.4f, 0.4f, 0.4f});
    renderer.transform.Translate({0.0f, -2.0f, 0.0f});

    audio.play(true);
    while (window.IsOpen()){
        window.Clear();


        renderer.transform.Rotate(1.0f, {0.0f, 1.0f, 0.0f});
        renderer.Render(window);

        window.Flip();
    }

    Eucalyptus::Terminate();
    return 0;   
}