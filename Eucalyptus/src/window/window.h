#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "windowConfig.h"

#include "math/vector.h"
#include "color/color.h"
#include "api.h"


namespace Eucalyptus{
    class _EUCAPI Window{
    public:
        Window(Math::Vector2i size, const char* name = "Eucalyptus");
        ~Window();

        void InitWindow();
        void Flip();

        void Clear(Color col = Color::DARK_GRAY);

        WindowConfig& GetConfig() { return m_config; };

        bool IsOpen() { return !glfwWindowShouldClose(m_window); };

        Math::Vector2i GetSize() { return m_size; }
        void SetSize(Math::Vector2i size) { m_size = size; }
    private:

        Math::Vector2i m_size;
        const char* m_name;

        GLFWwindow* m_window;
        WindowConfig m_config;
    };

    void _EUCAPI Terminate();

    void _EUCAPI Init();
}