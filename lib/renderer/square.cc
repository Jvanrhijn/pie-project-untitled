//
// Created by jesse on 10/31/18.
//
#include "lib/renderer/square.h"

namespace pie {

constexpr float Square::vertex_buffer_data_[];
constexpr GLuint Square::elements_[];

Square::Square(double x, double y, double side,
    const Texture& texture, const ShaderPipeline<Shader<GL_VERTEX_SHADER>, Shader<GL_FRAGMENT_SHADER>>& shader)
: Shape(x, y), Drawable(), texture_(texture), shader_(shader), side_(side)
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
  // bind shader
  shader_.Bind(*this);
  // bind buffers
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_), vertex_buffer_data_, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements_), elements_, GL_STATIC_DRAW);
}

long Square::vertex_offset() const {
  return vertex_offset_;
}

long Square::color_offset() const {
  return color_offset_;
}

long Square::texture_offset() const {
  return texture_offset_;
}

long Square::stride() const {
  return stride_;
}

void Square::Rotate(double angle) {
  angle_ = angle;
}

void Square::MoveTo(double x, double y) {
  location_.first = x;
  location_.second = y;
}

void Square::Draw(GLFWwindow *window) const {
  glBindTexture(GL_TEXTURE_2D, texture_.texture_id());
  mat4x4 model, project, mvp;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  float ratio = width/static_cast<float>(height);
  // transformation matrices
  mat4x4_identity(model);
  mat4x4_translate_in_place(model, location_.first, location_.second, 0.0f);
  mat4x4_rotate_Z(model, model, angle_);
  mat4x4_scale_aniso(model, model, side_, side_, 1.0f);
  mat4x4_ortho(project, -ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
  mat4x4_mul(mvp, project, model);
  // draw object
  shader_.Use((const float *)mvp);
  glEnableVertexAttribArray(0);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  glDisableVertexAttribArray(0);
}

} // namespace pie

