//
// Created by jesse on 10/31/18.
//

#ifndef __PIE_LIB_RENDERER_SQUARE_H
#define __PIE_LIB_RENDERER_SQUARE_H

#include <iostream>

#include "lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "lib/renderer/shape.h"
#include "lib/renderer/util/load_shader.h"
#include "lib/renderer/texture.h"
#include "lib/renderer/shader.h"
#include "lib/draw/drawable.h"
#include "lib/linmath.h"

namespace pie {

class Square : protected Shape, public Drawable<GLFWwindow> {
 public:
  /**
   * @brief Object for rendering squares, e.g. tiles
   * @param x x-location on the screen, (-1, 1)
   * @param y y-location on the screen, (-1, 1)
   * @param texture Texture object to draw on the square
   * @param shader Shader to render object with
   */
  Square(double x, double y, double side,
      const Texture& texture, const ShaderPipeline<Shader<GL_VERTEX_SHADER>, Shader<GL_FRAGMENT_SHADER>> &shader);
  ~Square() override = default;

  void Draw(GLFWwindow*) const override;

  // Getters
  long vertex_offset() const;
  long color_offset() const;
  long texture_offset() const;
  long stride() const;

 private:
  const Texture &texture_;
  const ShaderPipeline<Shader<GL_VERTEX_SHADER>, Shader<GL_FRAGMENT_SHADER>> &shader_;

  double side_;

  // OpenGL IDs
  GLuint vertex_array_id_;
  GLuint vertex_buffer_;
  GLuint element_buffer_;

  // Constants for this model
  //! vertex data (pos, color, texture coordinates)
  static constexpr float vertex_buffer_data_[] {
      -1.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
      1.0f,  -1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
      1.0f,   1.0f, 0.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
      -1.0f, 1.0f, 0.0f,      1.0f, 1.0f, 0.0f,   0.0f, 1.0f
  };

  //! Triangle element indices
  static constexpr GLuint elements_[] {
    0, 1, 2,
    2, 3, 0
  };

  // Offsets and stride for vertex_buffer_data_
  static constexpr int vertex_offset_{sizeof(float)*0};
  static constexpr int color_offset_{sizeof(float)*3};
  static constexpr int texture_offset_{sizeof(float)*6};
  static constexpr int stride_{sizeof(float)*8};

};

}

#endif // __PIE_LIB_RENDERER_SQUARE_H
