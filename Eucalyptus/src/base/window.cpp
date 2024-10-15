#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Eucalyptus/init.h>
#include <Eucalyptus/window.h>
#include <Eucalyptus/math/vector2.h>

#include <clog.h>


namespace Eucalyptus {
    Window::Window(Vector2u size, const char *title) : size(size), delta_time(0.0f) {
        if (!__gl_init) {
            clog(CLOG_FATAL, "OpenGL Is not initialized yet. Did you remember to call Eucalyptus::Init()?");
            Terminate();
            exit(1);
        }

        m_windowHints();
        m_window = glfwCreateWindow(size.x, size.y, title, nullptr, nullptr);
        if (m_window == nullptr) {
            clog(CLOG_FATAL, "Failed to create GLFWwindow. Check logs for more details.");
            Eucalyptus::Terminate();
            exit(1);
        }
        clog(CLOG_TRACE, "Created window, moving to Eucalyptus::Window::m_initializeWindow()");
        m_initializeWindow();
    }

    Window::Window(unsigned int width, unsigned int height, const char *title) : size({width, height}), delta_time(0.0f) {
        if (!__gl_init) {
            clog(CLOG_FATAL, "OpenGL Is not initialized yet. Did you remember to call Eucalyptus::Init()?");
            Terminate();
            exit(1);
        }

        m_windowHints();
        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (m_window == nullptr) {
            clog(CLOG_FATAL, "Failed to create GLFWwindow. Check logs for more details.");
            Eucalyptus::Terminate();
            exit(1);
        }
        clog(CLOG_TRACE, "Created window, moving to Eucalyptus::Window::m_initializeWindow()");
        m_initializeWindow();
    }

    void Window::m_initializeWindow() {
        glfwMakeContextCurrent((GLFWwindow*)m_window);
        clog(CLOG_TRACE, "Made window to current context");

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            clog(CLOG_FATAL, "Failed to initialize GLAD. Check logs for more details.");
            Eucalyptus::Terminate();
            exit(1);
        }
        glEnable(GL_DEPTH_TEST);
        glfwSwapInterval(1);
        running = true;
    }

    void Window::m_windowHints() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    }

    bool Window::IsRunning() {
        return running;
    }
    
    void Window::Update() {
        running = !glfwWindowShouldClose((GLFWwindow*)m_window);
        glfwSwapBuffers((GLFWwindow*)m_window);
        glfwPollEvents();
    }

    void Window::Clear(Color col) {
        glClearColor(col.r, col.g, col.b, col.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_now = glfwGetTime();
        delta_time = m_now - m_previous_time;
        m_previous_time = m_now;
    }
}