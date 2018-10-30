cmake_minimum_required(VERSION 3.9.2)

set(source_files
        src/board.cc
        src/tile.cc
        src/rules.cc)

add_library(sources STATIC ${source_files})
