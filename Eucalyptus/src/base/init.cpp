#include <Eucalyptus/init.h>
#include <GLFW/glfw3.h>

#include <clog.h>


void glfw_error_callback(int code, const char *msg) {
    clog(CLOG_ERROR, "Error code %i: %s", code, msg);
}

namespace Eucalyptus {
    bool __gl_init = false;
    bool __glad_init = false;

    void Init() {
        clog_set_fmt("%c[%L]:%r %m");
        glfwSetErrorCallback(glfw_error_callback);
        
        if (!glfwInit()) {
            clog(CLOG_FATAL, "Failed to initialize GLFW, check logs for more info.");
            exit(1);
        }
        __gl_init = true;
        clog(CLOG_INFO, "Initialized GLFW");
    }

    void Terminate() {
        clog(CLOG_INFO, "Application ran for %fs", glfwGetTime());
        glfwTerminate();
        clog(CLOG_INFO, "Terminated.");
        __gl_init = false;
        __glad_init = false;
    }
}