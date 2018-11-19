//
// Created by jesse on 10/30/18.
//

#ifndef __PIE_LIB_DRAW_RENDERER_H
#define __PIE_LIB_DRAW_RENDERER_H

#include <iostream>
#include <vector>
#include <memory>

#include "lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "lib/renderer/exceptions.h"
#include "lib/renderer/drawable.h"

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

  void AddObject(std::shared_ptr<Drawable<GLFWwindow>> object);

  //! Window getter
  GLFWwindow *window() const;


 private:
  //! Draw a drawable object
  void DrawObject(const Drawable<GLFWwindow> &object) const;

  void SetKeyCallbacks();

 private:
  size_t width_;
  size_t height_;
  GLFWwindow *window_;

  std::vector<std::shared_ptr<Drawable<GLFWwindow>>> objects_;
};

}

#endif //__PIE_LIB_DRAW_RENDERER_H
