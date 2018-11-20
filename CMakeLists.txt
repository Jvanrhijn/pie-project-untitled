cmake_minimum_required(VERSION 3.9.2)
project(pie)

set(TARGET pie)
set(OpenGL_GL_PREFERENCE GLVND)

set(UNIT_TESTS unit_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COVERAGE OFF CACHE BOOL "Coverage")

# compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_subdirectory(freetype2)

# include dirs
include_directories(.)
include_directories(freetype2)
include_directories(freetype2/include)


# include other CMakeLists
include(lib/renderer/CMakeLists.txt)
include(lib/glad/CMakeLists.txt)
include(lib/game/CMakeLists.txt)
include(lib/input/CMakeLists.txt)
include(lib/argparse/CMakeLists.txt)
include(tests/CMakeLists.txt)
include(gtest.cmake)

# OpenGL libraries
find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${TARGET} ${OPENGL_INCLUDE_DIR})

# code coverage analysis
if (COVERAGE)
  target_compile_options(unit_tests PRIVATE --coverage -g)
  target_link_libraries(unit_tests PRIVATE --coverage -g)
endif()

set (src_files
        src/game.cc
        src/game_tile.cc
        src/solver.cc)

# executables
add_executable(${TARGET} src/main.cc util/macros.h util/functions.h ${src_files})
target_link_libraries(${TARGET} ${OPENGL_gl_LIBRARY} glfw glad renderer game input argparse)
