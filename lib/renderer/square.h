//
// Created by jesse on 10/31/18.
//

#ifndef __PIE_LIB_RENDERER_SQUARE_H
#define __PIE_LIB_RENDERER_SQUARE_H

#include <iostream>

#include "glad.h"
#include <GLFW/glfw3.h>

#include "util/load_shader.h"
#include "texture.h"
#include "shader.h"
#include "drawable.h"
#include "linmath.h"

namespace pie {

// See Documentation of Drawable for inherited function docs
class Square : public Drawable<GLFWwindow> {
 public:
  /**
   * @brief Object for rendering squares, e.g. tiles
   * @param x x-location on the screen, (-1, 1)
   * @param y y-location on the screen, (-1, 1)
   * @param texture Texture object to draw on the square
   * @param shader Shader to render object with
   */
  Square(float x, float y, double side, const Texture& texture, const VFShader &shader);
  ~Square() override = default;

  void Draw(GLFWwindow*) const override;

  //! Set the color of the square
  void Color(const Color &color);

  // getters
  std::pair<double, double> location() const;

 private:
  const Texture &texture_;
  const VFShader &shader_;

  double side_;

  // OpenGL IDs
  GLuint vertex_array_id_;
  GLuint vertex_buffer_;
  GLuint element_buffer_;

  // Constants for this model
  //! vertex data (pos, color, texture coordinates)
  float vertex_buffer_data_[48]{
      -1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,
       1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
       1.0f,  1.0f, 1.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,

       1.0f,  1.0f, 1.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
      -1.0f,  1.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f,
      -1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f
  };

};

}

#endif // __PIE_LIB_RENDERER_SQUARE_H
