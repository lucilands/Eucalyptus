#pragma once

#include "math/vector2.h"
#include "math/color.h"



namespace Eucalyptus {
    class Window {
        public:
            Window(Vector2u size, const char *title);
            Window(unsigned int width, unsigned int height, const char *title);

            Vector2u size;
            bool running;

            bool IsRunning();
            void Update();
            void Clear(Color col);
        private:
            void m_initializeWindow();
            void m_windowHints();

            void *m_window;
    };
}