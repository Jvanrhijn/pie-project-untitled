cmake_minimum_required(VERSION 3.9.2)

set(renderer_files
        lib/renderer/renderer.cc)

add_library(renderer STATIC ${renderer_files})
target_link_libraries(renderer glfw3)
