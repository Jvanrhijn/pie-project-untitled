//
// Created by jesse on 10/31/18.
//
#include "lib/renderer/square.h"

namespace pie {

constexpr float Square::vertex_buffer_data_[];
constexpr GLuint Square::elements_[];

Square::Square(double x, double y, double side, const Texture& texture)
: Shape(x, y), Drawable(), texture_(texture), side_(side)
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
  // load shaders
  program_ = loadShaders(vertex_shader_path_, fragment_shader_path_);
  mvp_location_ = glGetUniformLocation(program_, "MVP");
  vpos_location_ = glGetAttribLocation(program_, "vPos");
  vcol_location_ = glGetAttribLocation(program_, "vCol");
  vtex_location_ = glGetAttribLocation(program_, "vTex");
  // set vertex attributes
  glVertexAttribPointer(vpos_location_, 3, GL_FLOAT, GL_FALSE, stride_, (void*)vertex_offset_);
  glEnableVertexAttribArray(vpos_location_); // vpos_location_
  glVertexAttribPointer(vcol_location_, 3, GL_FLOAT, GL_FALSE, stride_, (void*)color_offset_);
  glEnableVertexAttribArray(vcol_location_); // vcol_location_
  glVertexAttribPointer(vtex_location_, 2, GL_FLOAT, GL_FALSE, stride_, (void*)texture_offset_);
  glEnableVertexAttribArray(vtex_location_);
  // bind buffers
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_), vertex_buffer_data_, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements_), elements_, GL_STATIC_DRAW);
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
  mat4x4_scale_aniso(model, model, side_, side_, 1.0f);
  mat4x4_ortho(project, -ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
  mat4x4_mul(mvp, project, model);
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

