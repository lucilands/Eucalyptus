#pragma once

#include "math/vector2.h"
#include "math/vector4.h"
#include "math/color.h"
#include "input/input_dispatcher.h"
#include "input/keycodes.h"


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
            InputDispatcher input;

            bool IsRunning();
            void Update();
            void Clear(Vector4f col);
            void Close();
            static float GetDeltaTime() {return Eucalyptus::window->delta_time;}
            
            void *__get_gl() {return m_window;}
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