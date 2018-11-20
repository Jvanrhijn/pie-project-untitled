cmake_minimum_required(VERSION 3.9.2)

set(game_files
        board.cc
        tile.cc
        rules.cc)

add_library(game STATIC ${game_files})
