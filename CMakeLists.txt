cmake_minimum_required(VERSION 3.16)

project(EucalyptusT)

set(CMAKE_SHARED_LIBRARY_PREFIX "")



set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused -Wextra -Wall")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(Eucalyptus/CMakeLists.txt)
add_subdirectory(sandbox)

if(WIN32)
target_compile_definitions(Eucalyptus PUBLIC EUCALYPTUS_PLATFORM_WINDOWS)
endif(WIN32)
if(UNIX)
target_compile_definitions(Eucalyptus PUBLIC EUCALYPTUS_PLATFORM_LINUX)
endif(UNIX)

target_compile_definitions(Eucalyptus PUBLIC EUCALYPTUS_ENABLE_LOGGING)


target_link_libraries(Sandbox Eucalyptus)