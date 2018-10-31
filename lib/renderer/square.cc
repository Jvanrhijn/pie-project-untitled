//
// Created by jesse on 10/31/18.
//
#include "lib/renderer/square.h"

namespace pie {

constexpr GLfloat Square::vertex_buffer_data_[];

Square::Square(double x, double y, double side)
: Shape(x, y), Drawable(), side_(side)
{
  // Taken from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);
  glGenBuffers(1, &vertex_buffer_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Square::vertex_buffer_data_), vertex_buffer_data_, GL_STATIC_DRAW);
  // load shaders
  program_ = loadShaders("lib/renderer/shaders/vertex_shader_test.vertexshader", "lib/renderer/shaders/fragment_shader_test.fragmentshader");
}

void Square::Draw() const {
  glUseProgram(program_);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glVertexAttribPointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0,
      (void*)0
      );
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
}

const GLuint& Square::program() const {
  return program_;
}

} // namespace pie

