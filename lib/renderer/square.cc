//
// Created by jesse on 10/31/18.
//
#include "lib/renderer/square.h"

namespace pie {

Square::Square(double x, double y, double side, const Texture& texture, const VFShader& shader)
: Shape(x, y), Drawable(), texture_(texture), shader_(shader), side_(side), angle_(0.0)
{
  // Taken from:
  // http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
  // https://open.gl/drawing
  // bind vertex arrays and load texture
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);
  // generate buffers
  glGenBuffers(1, &vertex_buffer_);
  glGenBuffers(1, &element_buffer_);
  // bind buffers
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_), vertex_buffer_data_, GL_STATIC_DRAW);
  // bind shader
  shader_.Bind(*this);
}


void Square::Rotate(double angle) {
  angle_ = angle;
}

void Square::MoveTo(double x, double y) {
  location_.first = x;
  location_.second = y;
}

void Square::MoveAlong(double dx, double dy) {
  location_.first += dx;
  location_.second += dy;
}

void Square::Draw(GLFWwindow *window) const {
  glBindTexture(GL_TEXTURE_2D, texture_.texture_id());
  glBindVertexArray(vertex_array_id_);
  mat4x4 model, project, mvp;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  float ratio = width/static_cast<float>(height);
  // transformation matrices
  mat4x4_identity(model);
  mat4x4_translate_in_place(model, location_.first, location_.second, 0.0f);
  mat4x4_rotate_Z(model, model, angle_);
  mat4x4_scale_aniso(model, model, 0.5f*side_, 0.5f*side_, 1.0f); // factor since screen width is 2
  mat4x4_ortho(project, -ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
  mat4x4_mul(mvp, project, model);
  // draw object
  shader_.Use();
  glUniformMatrix4fv(glGetUniformLocation(shader_.program(), "MVP"), 1, GL_FALSE, (const float *) mvp);
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  // unbind array object and texture
  glDisableVertexAttribArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
}

void Square::Color(const struct Color &color) {
  constexpr auto stride = stride_/sizeof(float);
  constexpr auto offset = color_offset_/sizeof(float);
  for (size_t i=0; i<sizeof(vertex_buffer_data_)/stride_; i++) {
    vertex_buffer_data_[i*stride + offset + 0] = color.r;
    vertex_buffer_data_[i*stride + offset + 1] = color.g;
    vertex_buffer_data_[i*stride + offset + 2] = color.b;
  }
  // bind buffers
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_), vertex_buffer_data_, GL_STATIC_DRAW);
}

std::pair<double, double> Square::location() const {
  return location_;
}

} // namespace pie

