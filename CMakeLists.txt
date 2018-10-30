cmake_minimum_required(VERSION 3.9.2)
project(pie)

set(TARGET pie)
set(UNIT_TESTS unit_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COVERAGE OFF CACHE BOOL "Coverage")

# compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# include dirs
include_directories(.)

# include other CMakeLists
include(src/CMakeLists.txt)
include(tests/CMakeLists.txt)
include(lib/glad/CMakeLists.txt)
include(gtest.cmake)

# code coverage analysis
if(COVERAGE)
  target_compile_options(unit_tests PRIVATE --coverage)
  target_link_libraries(unit_tests PRIVATE --coverage)
endif()

# executables
add_executable(${TARGET} main.cc util/macros.h util/functions.h)
target_link_libraries(${TARGET} STATIC sources glad)
