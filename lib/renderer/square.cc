//
// Created by jesse on 10/31/18.
//
#include "lib/renderer/square.h"

namespace pie {

constexpr Square::vbuffer_ Square::vertex_buffer_data_[];
constexpr GLuint Square::elements_[];

Square::Square(double x, double y, double side)
: Shape(x, y), Drawable(), side_(side)
{
  // Taken from:
  // http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
  // https://open.gl/drawing
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);
  glGenBuffers(1, &vertex_buffer_);
  glGenBuffers(1, &element_buffer_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_), vertex_buffer_data_, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements_), elements_, GL_STATIC_DRAW);
  // load shaders
  program_ = loadShaders(vertex_shader_path_, fragment_shader_path_);
  mvp_location_ = glGetUniformLocation(program_, "MVP");
  vpos_location_ = glGetAttribLocation(program_, "vPos");
  vcol_location_ = glGetAttribLocation(program_, "vCol");
  glEnableVertexAttribArray(vpos_location_);
  glVertexAttribPointer(vpos_location_, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, nullptr);
  glEnableVertexAttribArray(vcol_location_);
  glVertexAttribPointer(vcol_location_, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)(sizeof(float)*2));
}

void Square::Draw(GLFWwindow *window) const {
  mat4x4 m, p, mvp;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  float ratio = width/static_cast<float>(height);
  // transformation matrices
  mat4x4_identity(m);
  mat4x4_ortho(p, -ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
  mat4x4_mul(mvp, p, m);
  // draw object
  glUseProgram(program_);
  // perform transformations
  glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, (const GLfloat*) mvp);
  glEnableVertexAttribArray(0);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  glDisableVertexAttribArray(0);
}

const GLuint& Square::program() const {
  return program_;
}

} // namespace pie

