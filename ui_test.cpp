#include <Eucalyptus.h>





int main() {
    Eucalyptus::Init();
    Eucalyptus::Window window = Eucalyptus::Window(Eucalyptus::Vector2u(1080, 720), "UI Testing");
    Eucalyptus::Scene main_scene = Eucalyptus::Scene();

    Eucalyptus::Panel panel = Eucalyptus::Panel(Eucalyptus::Vector2f(1000, 700), Eucalyptus::Vector2f(1080/2 - 500, 720/2 - 350), 0, Eucalyptus::Colors::White);
    panel.GetComponent<Eucalyptus::UI_Renderer>()->radius = 0.0f;


    while (window.IsRunning()) {
        window.Clear(Eucalyptus::Colors::LearnOpenGL);

        //panel.GetComponent<Eucalyptus::UI_Renderer>()->radius = abs(sin(Eucalyptus::window->time));

        main_scene.Update();
        window.Update();
    }

    Eucalyptus::Terminate();
    return 0;
}