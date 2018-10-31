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
#include "lib/draw/drawable.h"

namespace pie {

class Square : public Shape, public Drawable {
 public:
  Square(double x, double y, double side);
  ~Square() override = default;

  void Draw() const override;

  const GLuint& program() const;

 private:
  double side_;
  GLuint vertex_array_id_;
  GLuint vertex_buffer_;
  GLuint program_;

  //! Rendering details: (-1, -1) is the lower left corner
  static constexpr GLfloat vertex_buffer_data_[] {
      -1.0f, -1.0f, 0.0f,
      1.0f,  -1.0f, 0.0f,
      0.0f,   1.0f, 0.0f
  };

  static constexpr char const *vertex_shader_path_{"lib/renderer/shaders/vertex_shader_test.vertexshader"};
  static constexpr char const *fragment_shader_path_{"lib/renderer/shaders/fragment_shader_test.fragmentshader"};

};

}

#endif // __PIE_LIB_RENDERER_SQUARE_H
