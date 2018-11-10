//
// Created by jesse on 11/8/18.
//

#include "character.h"

namespace pie {

float Character::vertex_data_[] = {
  0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
  0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,

  0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
  0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f
};

Character::Character(FontFace &face, const char c, const Color& color, const VFShader &sp)
  : shader_(sp), color_(color), angle_(0.0f), location_(0.0f, 0.0f)
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
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // extract geometry info from glyph
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
}

void Character::Draw(GLFWwindow *window) const {
  glBindVertexArray(vao_);
  glBindTexture(GL_TEXTURE_2D, tex_id_);
  // define mvp matrix
  mat4x4 model, project, mvp;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  mat4x4_identity(model);
  mat4x4_translate_in_place(model, location_.first*width/2.0f, location_.second*height/2.0f, 0.0f);
  mat4x4_rotate_Z(model, model, angle_);
  mat4x4_scale_aniso(model, model, 1.0f, 1.0f, 1.0f);
  // convert model space coordinates to view space
  mat4x4_ortho(project, -width/2.0f, width/2.0f, -height/2.0f, height/2.0f, 1.0f, -1.0f);
  mat4x4_mul(mvp, project, model);
  shader_.Use();
  glUniformMatrix4fv(glGetUniformLocation(shader_.program(), "MVP"), 1, GL_FALSE, (const float *) mvp);
  glUniform3f(glGetUniformLocation(shader_.program(), "textColor"), color_.r, color_.g, color_.b);
  // render quad
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  // unbind array object and texture
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Character::MoveTo(double x, double y) {
  location_.first = x;
  location_.second = y;
}

void Character::MoveAlong(double dx, double dy) {
  location_.first += dx;
  location_.second += dy;
}

void Character::Rotate(double angle) {
  angle_ = angle;
}

GLuint Character::advance() const {
  return advance_;
}

std::pair<float, float> Character::location() const {
  return location_;
}

void Character::BuildVertices() {
  float xpos = bearing_.first;
  float ypos = bearing_.second - size_.second;
  constexpr auto stride = stride_/sizeof(float);
  // set vertex positions
  for (size_t i=0; i<6; i++) {
    vertex_data_[i*stride + 0] = xpos + size_.first/2.0f*(i == 0 || i == 1 || i == 3? -1.0f : 1.0f);
    vertex_data_[i*stride + 1] = ypos + size_.second/2.0f*(i == 1 || i == 2 || i == 4? -1.0f : 1.0f);
  }
  // generate vertex array
  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);
  // generate buffer object
  glGenBuffers(1, &vbo_);
  // bind buffer
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data_), vertex_data_, GL_STATIC_DRAW);
  // bind shader
  shader_.Bind(*this);
}

} // namespace pie