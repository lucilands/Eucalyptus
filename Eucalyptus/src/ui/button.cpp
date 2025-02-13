#include <Eucalyptus/ui/button.h>
#include <Eucalyptus/components/transform2d.h>
#include <Eucalyptus/window.h>





namespace Eucalyptus {
    Button::Button(Object *_) : Component(_) {
        is_hovered = false;
    }

    Button::Button(Object *_, ButtonFunc on_click) : Component(_) {
        is_hovered = false;
        this->on_click = on_click;
    }

    void Button::Update() {
        int x_min = m_parent->GetComponent<Transform2D>()->position.x;
        int x_max = m_parent->GetComponent<Transform2D>()->position.x + m_parent->GetComponent<Transform2D>()->size.x; 

        int y_min = m_parent->GetComponent<Transform2D>()->position.y;
        int y_max = m_parent->GetComponent<Transform2D>()->position.y + m_parent->GetComponent<Transform2D>()->size.y;

        Vector2f mouse_pos = window->input.GetMousePosition();
        if (mouse_pos.x > x_min && mouse_pos.x < x_max && mouse_pos.y > y_min && mouse_pos.y < y_max) {
            this->is_hovered = true;
        }
        else {this->is_hovered = false;}
        if (this->is_hovered && window->input.IsMousePressed()) {
            this->on_click(m_parent);
        }
    }
}