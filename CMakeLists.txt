cmake_minimum_required(VERSION 3.28)
project(Sandbox)
project(ui_test)

add_subdirectory(Eucalyptus)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)


add_executable(Sandbox sandbox.cpp)
add_executable(ui_test ui_test.cpp)

target_include_directories(Sandbox PRIVATE Eucalyptus/include)
target_link_libraries(Sandbox Eucalyptus)

target_include_directories(ui_test PRIVATE Eucalyptus/include)
target_link_libraries(ui_test Eucalyptus)

add_custom_command(TARGET Sandbox POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
