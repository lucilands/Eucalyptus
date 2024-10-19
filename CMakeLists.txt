cmake_minimum_required(VERSION 3.28)
project(Sandbox)

add_subdirectory(Eucalyptus)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

add_executable(Sandbox sandbox.cpp)

target_include_directories(Sandbox PRIVATE Eucalyptus/include)
target_link_libraries(Sandbox Eucalyptus)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})