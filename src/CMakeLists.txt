cmake_minimum_required(VERSION 3.11)

set (source_files
        src/board.cc
        src/tile.cc)

add_library(sources STATIC ${source_files})
