cmake_minimum_required(VERSION 3.28)
project(Eucalyptus)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

message(STATUS "Eucalyptus: Looking for OpenGL")
find_package(OpenGL REQUIRED)
message(STATUS "Eucalyptus: Found OpenGL")

if (NOT WIN32)
message(STATUS "Eucalyptus: Looking for GLFW")
find_package(glfw3 REQUIRED)
message(STATUS "Eucalyptus: Found GLFW")

message(STATUS "Eucalyptus: Looking for Nlohmann Json")
find_package(nlohmann_json 3.2.0 REQUIRED)
message(STATUS "Eucalyptus: Found Nlohmann Json")

else()

message(STATUS "Eucalyptus: Fetching and configuring GLFW3")
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/windeps/glfw3)
message(STATUS "Eucalyptus: Cloning GLFW3 from https://github.com/glfw/glfw.git")
execute_process(COMMAND git clone https://github.com/glfw/glfw.git ${CMAKE_CURRENT_SOURCE_DIR}/windeps/glfw3)
endif()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/windeps/glfw3)
set(OPENGL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/windeps/glfw3/include)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
message(STATUS "Eucalyptus: Fetched and configured GLFW3")

message(STATUS "Eucalypus: Fetching and configuring Nlohmann Json")
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/windeps/nlohmann_json)
message(STATUS "Eucalyptus: Cloning Nlohmann Json from https://github.com/nlohmann/json.git")
execute_process(COMMAND git clone https://github.com/nlohmann/json.git ${CMAKE_CURRENT_SOURCE_DIR}/windeps/nlohmann_json)
endif()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/windeps/nlohmann_json)
set(NLOHMANN_JSON_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/windeps/nlohmann_json/include)
message(STATUS "Eucalyptus: Fetched and configured Nlohmann Json")

endif()



add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/")

set(GLADDIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/")
set(CLOGDIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/clog/")
set(SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SRC_FILES "${SRCDIR}/clog.c"

              "${GLADDIR}/src/glad.c"

              "${SRCDIR}/input/input_dispatcher.cpp"

              "${SRCDIR}/ecs/object.cpp"
              "${SRCDIR}/ecs/scene.cpp"
              
              "${SRCDIR}/base/init.cpp" 
              "${SRCDIR}/base/window.cpp"
              
              "${SRCDIR}/components/model_renderer.cpp"
              "${SRCDIR}/components/transform.cpp"
              
              "${SRCDIR}/graphics/camera.cpp"
              "${SRCDIR}/graphics/shader.cpp"
              "${SRCDIR}/graphics/texture.cpp"
              
              "${SRCDIR}/loaders/glb.cpp"
              "${SRCDIR}/loaders/freader.cpp"
              
              "${SRCDIR}/ui/panel.cpp"
              "${SRCDIR}/ui/ui_renderer.cpp"
)
              
message(STATUS "Eucalyptus: Configuring shader strings in Eucalyptus/ui/ui_shaders.h")
file(READ "${SRCDIR}/ui/ui_panel.frag" FRAG_CONTENT)
file(READ "${SRCDIR}/ui/ui_panel.vert" VERT_CONTENT)

configure_file("${SRCDIR}/ui/ui_shaders.h.in" "${SRCDIR}/ui/ui_shaders.h" @ONLY)
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}"-fno-PIE")

add_library(Eucalyptus STATIC ${SRC_FILES})

target_include_directories(Eucalyptus PUBLIC "${CLOGDIR}")
target_include_directories(Eucalyptus PUBLIC "${GLADDIR}/include")
target_include_directories(Eucalyptus PUBLIC "${OPENGL_INCLUDES}")
target_include_directories(Eucalyptus PUBLIC "${NLOHMANN_JSON_INCLUDES}")
target_include_directories(Eucalyptus PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(Eucalyptus PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm")
target_include_directories(Eucalyptus PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb")

target_link_libraries(Eucalyptus PRIVATE glfw OpenGL::GL glm::glm nlohmann_json::nlohmann_json)
message(STATUS "Eucalyptus: Configured Eucalyptus")
