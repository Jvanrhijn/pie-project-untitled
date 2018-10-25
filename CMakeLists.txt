cmake_minimum_required(VERSION 3.11)
project(pie)
set(TARGET pie)
set(UNIT_TESTS unit_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 --coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# include dirs
include_directories(.)

# include other CMakeLists
include(src/CMakeLists.txt)
include(tests/CMakeLists.txt)

# executables
add_executable(${TARGET} main.cc ${SOURCES} util/macros.h)
target_link_libraries(${TARGET} sources)
