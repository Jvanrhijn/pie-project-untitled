cmake_minimum_required(VERSION 3.9.2)

find_package(FreeType)

include_directories(${FREETYPE_INCLUDE_DIRS})

set(renderer_files
        lib/renderer/renderer.cc
        lib/renderer/square.cc
        lib/renderer/util/load_shader.cc
        lib/renderer/texture.cc
        lib/renderer/text/character.cc
        lib/renderer/text/fontface.cc
        lib/renderer/text/charmap.cc
        lib/renderer/text/string.cc)

add_library(renderer STATIC ${renderer_files})
target_link_libraries(renderer glad glfw3 freetype)
