set(TARGET hopscotch)

set(OpenGL_GL_PREFERENCE GLVND)

set(src_files
        game.cc
        game_tile.cc
        main.cc)

add_executable(${TARGET} ${src_files})
target_link_libraries(${TARGET} ${OPENGL_gl_LIBRARY} glfw glad renderer game input argparse freetype)