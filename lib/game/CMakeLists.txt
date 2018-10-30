cmake_minimum_required(VERSION 3.9.2)

set(game_files
        lib/game/board.cc
        lib/game/tile.cc
        lib/game/rules.cc)

add_library(game STATIC ${game_files})
