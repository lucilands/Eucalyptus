#pragma once
#include <GLFW/glfw3.h>

#include <map>
#include <string>

#include "keycodes.h"


namespace Eucalyptus {
    class InputDispatcher {
        public:
            InputDispatcher() {}
            //InputDispatcher(GLFWwindow** window) : m_window(window) {}
            //InputDispatcher(void** window) : m_window((GLFWwindow**)window) {}
            static void _glfw_key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
            
            bool IsKeyPressed(Input::KeyCode code);
            bool IsKeyHeld(Input::KeyCode code);
            bool IsKeyReleased(Input::KeyCode code);

            void __set_window(GLFWwindow *win) {m_window = win;}

            int last_key = 0;
            int last_action = 0;

            std::map<char, bool> held_keys = {
                {'a', false},
                {'b', false},
                {'c', false},
                {'d', false},
                {'e', false},
                {'f', false},
                {'g', false},
                {'h', false},
                {'i', false},
                {'j', false},
                {'k', false},
                {'l', false},
                {'m', false},
                {'n', false},
                {'o', false},
                {'p', false},
                {'q', false},
                {'r', false},
                {'s', false},
                {'t', false},
                {'u', false},
                {'v', false},
                {'w', false},
                {'x', false},
                {'y', false},
                {'z', false},

                {'1', false},
                {'2', false},
                {'3', false},
                {'4', false},
                {'5', false},
                {'6', false},
                {'7', false},
                {'8', false},
                {'9', false},
                {'0', false}
            };

        private:
            GLFWwindow *m_window;
    };
}