cmake_minimum_required(VERSION 3.11)
project(pie)
set(TARGET pie)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add directories
include_directories(include)
include_directories(src)
add_subdirectory(src)

# glob sources
file(GLOB SOURCES src/*.cc)
file(GLOB TESTS tests/test_*.cc)

# gtest
add_subdirectory(tests)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(unit_tests tests/tests.cc ${TESTS} ${SOURCES})
find_package(Threads REQUIRED)
target_link_libraries(unit_tests gtest gtest_main Threads::Threads)
add_test(unit_tests unit_tests)

# link libraries
# nothing yet

# executable
add_executable(${TARGET} main.cc ${SOURCES} src/optional.h)

target_link_libraries(${TARGET} src)