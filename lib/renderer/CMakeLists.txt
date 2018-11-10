cmake_minimum_required(VERSION 3.9.2)

find_package(FreeType)

include_directories(${FREETYPE_INCLUDE_DIRS})

set(renderer_files
        lib/renderer/renderer.cc
        lib/renderer/shape.cc
        lib/renderer/square.cc
        lib/renderer/util/load_shader.cc
        lib/renderer/texture.cc
        lib/renderer/character.cc
        lib/renderer/fontface.cc)

add_library(renderer STATIC ${renderer_files})
target_link_libraries(renderer glad glfw3 freetype)
