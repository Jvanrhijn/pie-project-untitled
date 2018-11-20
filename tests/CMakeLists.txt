cmake_minimum_required(VERSION 3.9.2)
set (UNIT_TESTS unit_tests)

# required stuff for tests
find_package(Threads REQUIRED)

# include dirs for tests
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set (test_files
        test_grid.cc
        test_optional.cc
        test_tile.cc
        test_board.cc
        test_rules.cc
        test_argparse.cc)

# adding executable
add_executable(${UNIT_TESTS} tests.cc ${test_files})
target_link_libraries(${UNIT_TESTS} PRIVATE gtest Threads::Threads renderer game argparse)

# code coverage analysis
if (COVERAGE)
    target_compile_options(unit_tests PRIVATE --coverage -g)
    target_link_libraries(unit_tests PRIVATE --coverage -g)
endif()
