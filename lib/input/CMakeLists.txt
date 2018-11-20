cmake_minimum_required(VERSION 3.9.2)

set (input_files
        input.cc)

add_library(input STATIC ${input_files})
