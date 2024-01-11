project(Eucalyptus LANGUAGES CXX)


set(EUCDIR Eucalyptus/src)
set(VENDOR ../vendor)

add_library(Eucalyptus SHARED   
                ${EUCDIR}/internal.cpp
                ${VENDOR}/glad/src/glad.c
                ${EUCDIR}/color/color.cpp
                ${EUCDIR}/error/error.cpp
                ${EUCDIR}/light/light.cpp
                ${EUCDIR}/audio/audio.cpp
                ${EUCDIR}/shader/shader.cpp
                ${EUCDIR}/graphics/mesh.cpp
                ${EUCDIR}/window/window.cpp
                ${EUCDIR}/math/transform.cpp
                ${EUCDIR}/graphics/texture.cpp
                ${EUCDIR}/graphics/renderer.cpp
                ${EUCDIR}/graphics/material.cpp
                ${EUCDIR}/meshloader/loader.cpp
                ${EUCDIR}/window/windowConfig.cpp
                ${VENDOR}/easyloggingpp/src/easylogging++.cc)

target_include_directories(Eucalyptus PUBLIC "vendor/GLFW/include/")
target_include_directories(Eucalyptus PUBLIC "vendor/glad/include/")
target_include_directories(Eucalyptus PUBLIC "vendor/easyloggingpp/src/")
target_include_directories(Eucalyptus PUBLIC "vendor/stb/")
target_include_directories(Eucalyptus PUBLIC "vendor/glm/")
target_include_directories(Eucalyptus PUBLIC Eucalyptus/src)

if (WIN32)
    target_link_directories(Eucalyptus PUBLIC "vendor/GLFW/lib/static")
    target_link_libraries(Eucalyptus PUBLIC )
    target_link_libraries(Eucalyptus PUBLIC "opengl32.lib" "glfw3.lib" "winmm")
endif (WIN32)

if (UNIX)
    target_link_directories(Eucalyptus PUBLIC "vendor/GLFW/lib/linux")
    target_link_libraries(Eucalyptus PUBLIC "X11" "glfw3" "GL" "pthread")
endif(UNIX)

target_compile_definitions(Eucalyptus PUBLIC _EUCDLL)
