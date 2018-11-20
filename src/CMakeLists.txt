<<<<<<< HEAD
cmake_minimum_required(VERSION 3.9.2)

set (source_files
        src/board.cc
        src/tile.cc
        src/cli_draw.cc
        src/rules.cc
        src/solver.cc)

add_library(sources STATIC ${source_files})
=======
set(TARGET hopscotch)

set(OpenGL_GL_PREFERENCE GLVND)

set(src_files
        game.cc
        game_tile.cc
        main.cc)

add_executable(${TARGET} ${src_files})
target_link_libraries(${TARGET} ${OPENGL_gl_LIBRARY} glfw glad renderer game input argparse freetype)
>>>>>>> ca2595189d187537a2e40ab17ae42cea55f158c3
