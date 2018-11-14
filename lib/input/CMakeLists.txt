cmake_minimum_required(VERSION 3.9.2)

set (input_files
        lib/input/input.cc)

add_library(input STATIC ${input_files})
target_link_libraries(input glad glfw3)
