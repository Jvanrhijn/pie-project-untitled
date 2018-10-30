//
// Created by jesse on 10/30/18.
//

#ifndef __PIE_LIB_DRAW_RENDERER_H
#define __PIE_LIB_DRAW_RENDERER_H

#include <iostream>

#include "lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "lib/game/board.h"
#include "lib/exit_codes.h"

namespace pie {

/**
 * Renderer class, abstracts over OpenGL library to render the game to the screen
 */
class Renderer {
 public:
  /**
   * @brief Renderer constructor
   * @param width Width of the created window, px
   * @param height Height of the created window, px
   */
  Renderer(size_t width, size_t height);

  ~Renderer();

  //! Rendering loop
  void Loop() const;

  //! Window getter
  GLFWwindow *window() const;

  //! Draw a game board
  void DrawBoard(const Board &board) const;

 private:
  void SetKeyCallbacks();

 private:
  GLFWwindow *window_;
};

}

#endif //__PIE_LIB_DRAW_RENDERER_H
