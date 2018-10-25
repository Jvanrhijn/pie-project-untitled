cmake_minimum_required(VERSION 3.9.2)
set (UNIT_TESTS unit_tests)

set (test_files
        tests/test_grid.cc
        tests/test_optional.cc
        tests/test_tile.cc
        tests/test_board.cc)

# adding executable
add_executable(${UNIT_TESTS} tests/tests.cc ${test_files})
