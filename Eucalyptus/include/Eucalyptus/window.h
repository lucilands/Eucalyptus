#pragma once

#include "math/vector2.h"
#include "math/color.h"


namespace Eucalyptus {
    class Window;
    extern Window *window;
    
    class Window {
        public:
            Window(Vector2u size, const char *title);
            Window(unsigned int width, unsigned int height, const char *title);

            Vector2u size;
            bool running;
            float delta_time;
            float framerate;
            float time;

            bool IsRunning();
            void Update();
            void Clear(Color col);
            static float GetDeltaTime() {return Eucalyptus::window->delta_time;}
        private:
            void m_initializeWindow();
            void m_windowHints();

            void *m_window;

            float m_previous_time;
            float m_now;

            float m_frameCount;
            float m_previousTime;
    };
}