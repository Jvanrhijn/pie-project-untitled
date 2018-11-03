//
// Created by jesse on 11/1/18.
//

#ifndef PIE_SHADER_H_H
#define PIE_SHADER_H_H

#include <string>

#include "lib/renderer/util/load_shader.h"

namespace pie {

class Program {
 public:
  explicit Program(const std::string &vs, const std::string &fs);
  ~Program() = default;

  GLuint program() const;

 private:
  GLuint program_;
};

class Shader {
 public:
  explicit Shader(const std::string &vs, const std::string &fs);
  ~Shader() = default;

  template<class T>
  void Bind(T& drawable) const {
    glVertexAttribPointer(vpos_loc_, 3, GL_FLOAT, GL_FALSE, drawable.stride(), (void*)drawable.vertex_offset());
    glEnableVertexAttribArray(vpos_loc_); // vpos_location_
    glVertexAttribPointer(vcol_loc_, 3, GL_FLOAT, GL_FALSE, drawable.stride(), (void*)drawable.color_offset());
    glEnableVertexAttribArray(vcol_loc_); // vcol_location_
    glVertexAttribPointer(vtex_loc_, 2, GL_FLOAT, GL_FALSE, drawable.stride(), (void*)drawable.texture_offset());
    glEnableVertexAttribArray(vtex_loc_);
  }

  void Use(const float *mvp) const;

 private:
  Program CompileShader();

 private:
  std::string vs_;
  std::string fs_;
  Program program_;

  GLuint mvp_loc_;
  GLuint vpos_loc_;
  GLuint vcol_loc_;
  GLuint vtex_loc_;

};

} // namespace pie

#endif //PIE_SHADER_H_H
