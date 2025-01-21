#include <Eucalyptus/input/input_dispatcher.h>
#include <Eucalyptus/window.h>

#include <GLFW/glfw3.h>
#include <stdio.h>




namespace Eucalyptus {
    void InputDispatcher::_glfw_key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
        InputDispatcher *self = (InputDispatcher*)glfwGetWindowUserPointer(win);
        self->last_key = -1;
        self->last_action = -1;

        if (action == GLFW_PRESS) {
            self->held_keys[(char)(key + 32)] = true;
            self->last_key = key;
            self->last_action = action;
        }
        if (action == GLFW_RELEASE) {
            self->held_keys[(char)(key + 32)] = false;
            self->last_key = key;
            self->last_action = action;
        }

    }

    bool InputDispatcher::IsKeyPressed(Input::KeyCode code) {
        bool ret = (last_action == GLFW_PRESS) && (last_key == static_cast<int>(code));
        return ret;
    }

    bool InputDispatcher::IsKeyReleased(Input::KeyCode code) {
        bool ret = (last_action == GLFW_RELEASE) && (last_key == static_cast<int>(code));
        return ret;
    }

    bool InputDispatcher::IsKeyHeld(Input::KeyCode code) {
        return glfwGetKey((GLFWwindow*)Eucalyptus::window->__get_gl(), static_cast<int>(code)) == GLFW_PRESS;
    }

    Vector2f InputDispatcher::GetMousePosition() {
        double x, y;
        glfwGetCursorPos((GLFWwindow*)Eucalyptus::window->__get_gl(), &x, &y);
        return (Vector2f) {static_cast<float>(x), static_cast<float>(y)};
    }
}