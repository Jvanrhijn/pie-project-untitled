cmake_minimum_required(VERSION 3.11)
project(pie)
set(TARGET pie)
set(UNIT_TESTS unit_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include dirs
include_directories(lib src)

# include other CMakeLists
include(src/CMakeLists.txt)
include(tests/CMakeLists.txt)

# executables
add_executable(${TARGET} main.cc ${SOURCES})
target_link_libraries(${TARGET} sources)
