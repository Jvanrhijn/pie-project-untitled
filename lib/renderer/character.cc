//
// Created by jesse on 11/8/18.
//

#include "lib/renderer/character.h"

namespace pie {

Character::Character(FontFace &face, const char c)
  : c_(c)
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
  advance_ = face.face()->glyph->advance.x;
}

void Character::Draw(GLFWwindow *window) const {

}

} // namespace pie