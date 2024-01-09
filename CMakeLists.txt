cmake_minimum_required(VERSION 3.16)

project(EucalyptusT)

set(CMAKE_SHARED_LIBRARY_PREFIX "")



set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused -Wextra -Wall")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(Eucalyptus/CmakeLists.txt)
add_subdirectory(sandbox)

target_compile_definitions(Eucalyptus PUBLIC EUCALYPTUS_PLATFORM_WINDOWS)
target_compile_definitions(Eucalyptus PUBLIC EUCALYPTUS_ENABLE_LOGGING)


target_link_libraries(Sandbox Eucalyptus)