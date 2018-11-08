//
// Created by jesse on 11/8/18.
//

#include "lib/renderer/character.h"

namespace pie {

float Character::vertex_data_[24] = {
  0.0f, 0.0f,    0.0f, 0.0f,
  0.0f, 0.0f,    0.0f, 1.0f,
  0.0f, 0.0f,    1.0f, 1.0f,

  0.0f, 0.0f,    0.0f, 0.0f,
  0.0f, 0.0f,    1.0f, 1.0f,
  0.0f, 0.0f,    1.0f, 0.0f
};

Character::Character(FontFace &face, const char c, const VSShader &sp)
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
  size_ = std::make_pair(face.face()->glyph->bitmap.width, face.face()->glyph->bitmap.rows);
  bearing_ = std::make_pair(
      static_cast<int>(face.face()->glyph->bitmap_left),
      static_cast<int>(face.face()->glyph->bitmap_top)
  );
  advance_ = static_cast<GLuint>(face.face()->glyph->advance.x);
  // build vertex data
  this->BuildVertices();
}

void Character::Draw(GLFWwindow *window) const {

}

void Character::BuildVertices() {
  new (vertex_data_) float(0.0);
  float xpos = bearing_.first;
  float ypos = bearing_.second - size_.second;
  float w = size_.first;
  float h = size_.second;
  vertex_data_[0*stride_ + 1] = xpos;
  vertex_data_[0*stride_ + 1] = ypos + h;
  vertex_data_[1*stride_ + 0] = xpos;
  vertex_data_[1*stride_ + 1] = ypos;
  vertex_data_[2*stride_ + 0] = xpos + w;
  vertex_data_[2*stride_ + 1] = ypos;
  vertex_data_[3*stride_ + 0] = xpos;
  vertex_data_[3*stride_ + 1] = ypos + h;
  vertex_data_[4*stride_ + 0] = xpos + w;
  vertex_data_[4*stride_ + 1] = ypos;
  vertex_data_[5*stride_ + 0] = xpos + w;
  vertex_data_[5*stride_ + 1] = ypos + h;
}

} // namespace pie