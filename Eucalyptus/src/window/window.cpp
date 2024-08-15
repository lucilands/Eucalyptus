#include "window.h"
#include "error/error.h"

#include "shader/shader.h"
#include "graphics/mesh.h"

#include "log/logger.h"

#include "globals.h"

bool _GLINIT = false;
bool _EUCINIT = false;

namespace Eucalyptus{

    void framebuffer_size_callback(GLFWwindow* _window, int width, int height)
    {
        glfwMakeContextCurrent(_window);
        glViewport(0, 0, width, height);

        Window *window = static_cast<Window*>(glfwGetWindowUserPointer(_window));
        window->SetSize({width, height});
    }

    Window::Window(Math::Vector2i size, const char* name) : m_size(size), m_name(name), m_config(WindowConfig()){
        if (!_EUCINIT){
            _EUC_LOG_FATAL(EUCInitError("Eucalyptus is not initialized yet").ToString().c_str());
            Terminate();
            exit(1);
        }
        
    }
    Window::~Window(){
        glfwDestroyWindow(m_window);
    }

    void Window::InitWindow(){
        _EUC_LOG_INFO("Applying WindowConfig");
        glfwWindowHint(GLFW_RESIZABLE, m_config[WINDOW_CONFIG_RESIZABLE]);
        glfwWindowHint(GLFW_VISIBLE, m_config[WINDOW_CONFIG_VISIBLE]);
        glfwWindowHint(GLFW_DECORATED, m_config[WINDOW_CONFIG_DECORATED]);
        glfwWindowHint(GLFW_FOCUSED, m_config[WINDOW_CONFIG_FOCUSED]);
        glfwWindowHint(GLFW_AUTO_ICONIFY, m_config[WINDOW_CONFIG_AUTO_ICONIFY]);
        glfwWindowHint(GLFW_FLOATING, m_config[WINDOW_CONFIG_FLOATING]);
        glfwWindowHint(GLFW_MAXIMIZED, m_config[WINDOW_CONFIG_MAXIMIZED]);
        glfwWindowHint(GLFW_CENTER_CURSOR, m_config[WINDOW_CONFIG_CENTER_CURSOR]);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, m_config[WINDOW_CONFIG_TRANSPARENT_FRAMEBUFFER]);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, m_config[WINDOW_CONFIG_AUTO_FOCUS_SHOW]);
        glfwWindowHint(GLFW_SCALE_TO_MONITOR, m_config[WINDOW_CONFIG_SCALE_TO_MONITOR]);

        glfwWindowHint(GLFW_RED_BITS, m_config[WINDOW_CONFIG_COLOR_RED_BITS]);
        glfwWindowHint(GLFW_GREEN_BITS, m_config[WINDOW_CONFIG_COLOR_GREEN_BITS]);
        glfwWindowHint(GLFW_BLUE_BITS, m_config[WINDOW_CONFIG_COLOR_BLUE_BITS]);
        glfwWindowHint(GLFW_ALPHA_BITS, m_config[WINDOW_CONFIG_COLOR_ALPHA_BITS]);

        glfwWindowHint(GLFW_DEPTH_BITS, m_config[WINDOW_CONFIG_BUFFER_DEPTH_BITS]);
        glfwWindowHint(GLFW_STENCIL_BITS, m_config[WINDOW_CONFIG_BUFFER_STENCIL_BITS]);
        glfwWindowHint(GLFW_SRGB_CAPABLE, m_config[WINDOW_CONFIG_BUFFER_COLOR_SRGB]);

        glfwWindowHint(GLFW_SAMPLES, m_config[WINDOW_CONFIG_RENDER_MULTISAMPLES]);
        glfwWindowHint(GLFW_DOUBLEBUFFER, m_config[WINDOW_CONFIG_RENDER_DOUBLEBUFFER]);
        glfwWindowHint(GLFW_STEREO, m_config[WINDOW_CONFIG_RENDER_STEREO]);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_config[WINDOW_CONFIG_GLFW_CTX_VERSION_MAJOR]);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_config[WINDOW_CONFIG_GLFW_CTX_VERSION_MINOR]);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        _EUC_LOG_INFO("Creating GLFW window");
        m_window = glfwCreateWindow(m_size.x, m_size.y, m_name, NULL, NULL);

        glfwSetWindowUserPointer(m_window, this);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

        _EUC_LOG_INFO("Creating GLFW context");
        glfwMakeContextCurrent(m_window);

        if (m_window == NULL){
            _EUC_LOG_FATAL((GLFWWindowError("Failed to initialize window").ToString().c_str()));
            Terminate();
            exit(1);
        }
        _EUC_LOG_INFO("GLFW window created");

        _EUC_LOG_INFO("Initializing glad");
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            _EUC_LOG_FATAL(GLADInitError("Failed to initialize GLAD").ToString().c_str());
            Terminate();
            exit(1);
        }
        _EUC_LOG_INFO("Initialized glad");
        _GLINIT = true;

        
        glEnable(GL_DEPTH_TEST);  
        Shader::_InitShader();
        Mesh::_InitializeMeshes();
    }
    void Window::Flip(){
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void Window::Clear(Color col) {
        glClearColor(__COLOR_TO_ARGS(col));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Init(){
        _EUC_LOG_INFO("Initializing GLFW");
        if (glfwInit() == GLFW_FALSE){
            _EUC_LOG_FATAL((GLFWInitError("Failed to initialize GLFW").ToString().c_str()));
            Terminate();
            exit(1);
        }
        _EUC_LOG_INFO("Initialized GLFW");

        
        
        _EUCINIT = true;
    }
    void _EUCAPI Terminate(){
        for (Shader* s : shaders.get_list()) {
            s->Delete();
            free(s);
        }
        glfwTerminate();
    }
}