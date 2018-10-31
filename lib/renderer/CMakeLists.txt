cmake_minimum_required(VERSION 3.9.2)

set(renderer_files
        lib/renderer/renderer.cc
        lib/renderer/shape.cc
        lib/renderer/square.cc
        lib/renderer/util/load_shader.cc)

add_library(renderer STATIC ${renderer_files})
target_link_libraries(renderer glad glfw3)
