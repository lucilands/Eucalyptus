#include <Eucalyptus.h>



void on_click(Eucalyptus::Object *parent) {
    printf("Hello, World!\n");
}

int main() {
    Eucalyptus::Init();
    Eucalyptus::Window window = Eucalyptus::Window(Eucalyptus::Vector2u(1080, 720), "UI Testing");
    Eucalyptus::Scene main_scene = Eucalyptus::Scene();

    Eucalyptus::Panel panel = Eucalyptus::Panel(Eucalyptus::Vector2f(100, 100), Eucalyptus::Vector2f(1080/2 - 50, 720/2 - 50), 0, Eucalyptus::Colors::White);
    panel.GetComponent<Eucalyptus::UI_Renderer>()->radius = 0.1f;
    panel.AddComponent<Eucalyptus::Button>(on_click);

    while (window.IsRunning()) {
        window.Clear(Eucalyptus::Colors::LearnOpenGL);

        main_scene.Update();
        window.Update();
    }

    Eucalyptus::Terminate();
    return 0;
}