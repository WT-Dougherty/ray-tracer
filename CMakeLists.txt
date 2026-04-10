# from root:
#   cmake -B build/Release -DCMAKE_BUILD_TYPE=Release
#   cd build/release
#   ./Main > ../../output.ppm

cmake_minimum_required ( VERSION 3.1.0...4.0.0 )

project(RayTracing)

set( CMAKE_CXX_STANDARD            17)
set( CMAKE_CXX_STANDARD_REQUIRED TRUE)

set( SOURCE_ENUM
    src/main.cpp
    src/Sphere.cpp
    src/Camera.cpp)

message (STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
message (STATUS "Release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
message (STATUS "Debug flags: " ${CMAKE_CXX_FLAGS_DEBUG})
include_directories(src)

add_executable(Main ${SOURCE_ENUM})