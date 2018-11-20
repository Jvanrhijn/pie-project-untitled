cmake_minimum_required(VERSION 3.9.2)
project(pie)

set(OpenGL_GL_PREFERENCE GLVND)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COVERAGE OFF CACHE BOOL "Coverage")

# compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_subdirectory(freetype2)

# include dirs
include_directories(lib)
include_directories(util)
include_directories(freetype2/include)
include_directories(lib/glad/include/glad)

# OpenGL libraries
find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)
