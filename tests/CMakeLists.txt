cmake_minimum_required(VERSION 3.11)
set (UNIT_TESTS unit_tests)

# required stuff for tests
find_package(Threads REQUIRED)


# include dirs for tests
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(.)

set (test_files
        tests/test_grid.cc
        tests/test_optional.cc
        tests/test_tile.cc)

# adding executable
add_executable(${UNIT_TESTS} tests/tests.cc ${test_files})
target_link_libraries(${UNIT_TESTS} gtest gtest_main Threads::Threads sources)
