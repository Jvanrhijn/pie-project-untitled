//
// Created by jesse on 11/8/18.
//

#include "lib/renderer/character.h"

namespace pie {

float Character::vertex_data_[] = {
  0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
  0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,

  0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
  0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f
};

Character::Character(FontFace &face, const char c, const VFShader &sp)
  : c_(c), shader_(sp)
{
  face.LoadChar(c);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  // generate texture
  glGenTextures(1, &tex_id_);
  glBindTexture(GL_TEXTURE_2D, tex_id_);
  glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      face.face()->glyph->bitmap.width,
      face.face()->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      face.face()->glyph->bitmap.buffer
  );
  // set texture options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  size_ = std::make_pair(
      face.face()->glyph->bitmap.width,
      face.face()->glyph->bitmap.rows
  );
  bearing_ = std::make_pair(
      static_cast<int>(face.face()->glyph->bitmap_left),
      static_cast<int>(face.face()->glyph->bitmap_top)
  );
  advance_ = static_cast<GLuint>(face.face()->glyph->advance.x);
  // build vertex data
  this->BuildVertices();
  // bind shader
  shader_.Bind(*this);
}

void Character::Draw(GLFWwindow *window) const {
  // define mvp matrix
  mat4x4 model, project, mvp;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  float ratio = width/static_cast<float>(height);
  mat4x4_identity(model);
  mat4x4_ortho(project, -ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
  mat4x4_mul(mvp, project, model);
  // draw text
  shader_.Use((const float *) mvp);
  glUniform3f(glGetUniformLocation(shader_.program(), "textColor"), 0.5, 0.8, 0.2);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(vao_);
  // render glyph texture over quad
  glBindTexture(GL_TEXTURE_2D, tex_id_);
  // update content of VBO
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_data_), vertex_data_);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // render quad
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Character::MoveTo(double x, double y) {

}

void Character::Rotate(double angle) {

}

void Character::BuildVertices() {
  float xpos = bearing_.first;
  float ypos = bearing_.second - size_.second;
  float w = size_.first;
  float h = size_.second;
  auto stride = stride_/sizeof(float);
  vertex_data_[0*stride + 1] = xpos;
  vertex_data_[0*stride + 1] = ypos + h;
  vertex_data_[1*stride + 0] = xpos;
  vertex_data_[1*stride + 1] = ypos;
  vertex_data_[2*stride + 0] = xpos + w;
  vertex_data_[2*stride + 1] = ypos;
  vertex_data_[3*stride + 0] = xpos;
  vertex_data_[3*stride + 1] = ypos + h;
  vertex_data_[4*stride + 0] = xpos + w;
  vertex_data_[4*stride + 1] = ypos;
  vertex_data_[5*stride + 0] = xpos + w;
  vertex_data_[5*stride + 1] = ypos + h;
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data_), nullptr, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride_*sizeof(float), nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

} // namespace pie