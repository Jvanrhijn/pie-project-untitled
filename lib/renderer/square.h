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
#include "lib/draw/drawable.h"
#include "lib/linmath.h"

namespace pie {

class Square : protected Shape, public Drawable<GLFWwindow> {
 public:
  Square(double x, double y, double side, const Texture& texture);
  ~Square() override = default;

  void Draw(GLFWwindow*) const override;

  const GLuint& program() const;

 private:
  const Texture &texture_;

  double side_;
  GLuint vertex_array_id_;
  GLuint vertex_buffer_;
  GLuint element_buffer_;
  GLuint program_;

  // shader data
  GLint mvp_location_;
  GLint vpos_location_;
  GLint vcol_location_;
  GLint vtex_location_;

  //! Rendering details: (-1, -1) is the lower left corner
  static constexpr float vertex_buffer_data_[] {
      -1.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
      1.0f,  -1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
      1.0f,   1.0f, 0.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
      -1.0f, 1.0f, 0.0f,      1.0f, 1.0f, 0.0f,   0.0f, 1.0f
  };

  static constexpr GLuint elements_[] {
    0, 1, 2,
    2, 3, 0
  };

  static constexpr int vertex_offset_{sizeof(float)*0};
  static constexpr int color_offset_{sizeof(float)*3};
  static constexpr int texture_offset_{sizeof(float)*6};

  static constexpr int stride_{sizeof(float)*8};

  static constexpr char const *vertex_shader_path_{"lib/renderer/shaders/vertex_shader_test.vertexshader"};
  static constexpr char const *fragment_shader_path_{"lib/renderer/shaders/fragment_shader_test.fragmentshader"};
  static constexpr char const *texture_path_{"textures/paper.jpg"};

};

}

#endif // __PIE_LIB_RENDERER_SQUARE_H
