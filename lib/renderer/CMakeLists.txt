cmake_minimum_required(VERSION 3.9.2)

set(renderer_files
        renderer.cc
        square.cc
        util/load_shader.cc
        texture.cc
        text/character.cc
        text/fontface.cc
        text/charmap.cc
        text/string.cc)

add_library(renderer STATIC ${renderer_files})
