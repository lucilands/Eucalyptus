#include <Eucalyptus.h>





int main() {
    Eucalyptus::Init();
    Eucalyptus::Window window = Eucalyptus::Window(Eucalyptus::Vector2u(1080, 720), "UI Testing");
    Eucalyptus::Scene main_scene = Eucalyptus::Scene();

    while (window.IsRunning()) {

        main_scene.Update();
        window.Update();
    }

    Eucalyptus::Terminate();
    return 0;
}