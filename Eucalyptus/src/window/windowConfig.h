#pragma once
#include "api.h"

#include <GLFW/glfw3.h>



#define WINDOW_CONFIG_RESIZABLE 0
#define WINDOW_CONFIG_VISIBLE 1
#define WINDOW_CONFIG_DECORATED 2
#define WINDOW_CONFIG_FOCUSED 3
#define WINDOW_CONFIG_AUTO_ICONIFY 4
#define WINDOW_CONFIG_FLOATING 5
#define WINDOW_CONFIG_MAXIMIZED 6
#define WINDOW_CONFIG_CENTER_CURSOR 7
#define WINDOW_CONFIG_TRANSPARENT_FRAMEBUFFER 8
#define WINDOW_CONFIG_AUTO_FOCUS_SHOW 9
#define WINDOW_CONFIG_SCALE_TO_MONITOR 10

#define WINDOW_CONFIG_COLOR_RED_BITS 11
#define WINDOW_CONFIG_COLOR_GREEN_BITS 12
#define WINDOW_CONFIG_COLOR_BLUE_BITS 13
#define WINDOW_CONFIG_COLOR_ALPHA_BITS 14

#define WINDOW_CONFIG_BUFFER_DEPTH_BITS 15
#define WINDOW_CONFIG_BUFFER_STENCIL_BITS 16
#define WINDOW_CONFIG_BUFFER_COLOR_SRGB 17

#define WINDOW_CONFIG_RENDER_STEREO 18
#define WINDOW_CONFIG_RENDER_MULTISAMPLES 19
#define WINDOW_CONFIG_RENDER_DOUBLEBUFFER 20

#define WINDOW_CONFIG_GLFW_CTX_VERSION_MAJOR 21
#define WINDOW_CONFIG_GLFW_CTX_VERSION_MINOR 22

#define WINDOW_CONFIG_TRUE 1
#define WINDOW_CONFIG_FALSE 0

namespace Eucalyptus {
    class _EUCAPI WindowConfig {
    public:
        WindowConfig();
        int WindowConfigFlags[23]= {
            WINDOW_CONFIG_TRUE,
            WINDOW_CONFIG_TRUE,
            WINDOW_CONFIG_TRUE,
            WINDOW_CONFIG_TRUE,
            WINDOW_CONFIG_TRUE,
            WINDOW_CONFIG_FALSE,
            WINDOW_CONFIG_FALSE,
            WINDOW_CONFIG_TRUE,
            WINDOW_CONFIG_FALSE,
            WINDOW_CONFIG_TRUE,
            WINDOW_CONFIG_FALSE,
            8,
            8,
            8,
            8,
            24,
            8,
            WINDOW_CONFIG_FALSE,
            WINDOW_CONFIG_FALSE,
            0,
            WINDOW_CONFIG_TRUE,
            3,
            3
        };


        int& operator[](int idx){
            return WindowConfigFlags[idx];
        }
    };
}