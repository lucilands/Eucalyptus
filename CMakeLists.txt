cmake_minimum_required(VERSION 3.28)
project(Sandbox)

add_subdirectory(Eucalyptus)

add_executable(Sandbox sandbox.cpp)
target_include_directories(Sandbox PRIVATE Eucalyptus/include)
target_link_libraries(Sandbox Eucalyptus)