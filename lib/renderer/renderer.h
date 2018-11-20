//
// Created by jesse on 10/30/18.
//

#ifndef __PIE_LIB_DRAW_RENDERER_H
#define __PIE_LIB_DRAW_RENDERER_H

#include <iostream>
#include <vector>
#include <memory>

#include "glad.h"
#include <GLFW/glfw3.h>

#include "exceptions.h"
#include "drawable.h"

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

  //! Adds a drawable object to the renderer
  void AddObject(std::shared_ptr<Drawable<GLFWwindow>> object);

  //! Clears all objects from the render buffer
  void Clear();

  template<class Fn>
  void SetKeyCallback(Fn callback) {
    glfwSetKeyCallback(window_, callback);
  }

  //! Window getter
  GLFWwindow *window() const;

 private:
  //! Draw a drawable object
  void DrawObject(const Drawable<GLFWwindow> &object) const;

 private:
  size_t width_;
  size_t height_;
  GLFWwindow *window_;

  std::vector<std::shared_ptr<Drawable<GLFWwindow>>> objects_;
};

}

#endif //__PIE_LIB_DRAW_RENDERER_H
