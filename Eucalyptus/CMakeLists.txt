cmake_minimum_required(VERSION 3.28)
project(Eucalyptus)

message(STATUS "Eucalyptus: Looking for OpenGL")
find_package(OpenGL REQUIRED)
message(STATUS "Eucalyptus: Found OpenGL")
message(STATUS "Eucalyptus: Looking for GLFW")
find_package(glfw3 3.3.10 REQUIRED STATIC)
message(STATUS "Eucalyptus: Found GLFW")
message(STATUS "Eucalyptus: Looking for nlohmann/json")
find_package(nlohmann_json 3.2.0 REQUIRED)
message(STATUS "Eucalyptus: Found nlohmann/json")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/")

set(GLADDIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/")
set(CLOGDIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/clog/")
set(SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SRC_FILES "${SRCDIR}/clog.c"

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

              "${GLADDIR}/src/glad.c"
)

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}"-fno-PIE")

add_library(Eucalyptus STATIC ${SRC_FILES})

target_include_directories(Eucalyptus PRIVATE "${CLOGDIR}")
target_include_directories(Eucalyptus PRIVATE "${GLADDIR}/include")
target_include_directories(Eucalyptus PRIVATE "${OPENGL_INCLUDES}")
target_include_directories(Eucalyptus PRIVATE "${NLOHMANN_JSON_INCLUDES}")
target_include_directories(Eucalyptus PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(Eucalyptus PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm")
target_include_directories(Eucalyptus PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb")

target_link_libraries(Eucalyptus PRIVATE glfw OpenGL::GL glm::glm nlohmann_json::nlohmann_json)
message(STATUS "Eucalyptus: Configured Eucalyptus")
