cmake_minimum_required(VERSION 3.9.2)

set(glad_files
        lib/glad/src/glad.c)

add_library(glad STATIC ${glad_files})
