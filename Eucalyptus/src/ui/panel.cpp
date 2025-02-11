#include <Eucalyptus/ui/panel.h>
#include <Eucalyptus/ui/ui_renderer.h>

#include <Eucalyptus/components/transform2d.h>





namespace Eucalyptus {
    Panel::Panel(Vector2f size)                                                    : Object() {m_init(size, {0.0f, 0.0f}, 0, {1.0f, 1.0f, 1.0f, 1.0f});}
    Panel::Panel(Vector2f size, Vector4f color)                                    : Object() {m_init(size, {0.0f, 0.0f}, 0, color);}
    Panel::Panel(Vector2f size, Vector2f position)                                 : Object() {m_init(size, position, 0, {1.0f, 1.0f, 1.0f, 1.0f});}
    Panel::Panel(Vector2f size, float rotation)                                    : Object() {m_init(size, {0.0f, 0.0f}, rotation, {1.0f, 1.0f, 1.0f, 1.0f});}
    Panel::Panel(Vector2f size, Vector2f position, float rotation)                 : Object() {m_init(size, position, rotation, {1.0f, 1.0f, 1.0f, 1.0f});}
    Panel::Panel(Vector2f size, Vector2f position, float rotation, Vector4f color) : Object() {m_init(size, position, rotation, color);}

    void Panel::m_init(Vector2f size, Vector2f position, float rotation, Vector4f color) {
        AddComponent<UI_Renderer>();
        GetComponent<Transform2D>()->size = size;
        GetComponent<Transform2D>()->position = position;
        GetComponent<Transform2D>()->rotation = rotation;
        GetComponent<UI_Renderer>()->color = color;
    }
}