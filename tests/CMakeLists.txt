cmake_minimum_required(VERSION 3.11)
set (UNIT_TESTS unit_tests)

set (test_files
        tests/test_grid.cc
        tests/test_optional.cc
        tests/test_tile.cc)

# adding executable
add_executable(${UNIT_TESTS} tests/tests.cc ${test_files})
