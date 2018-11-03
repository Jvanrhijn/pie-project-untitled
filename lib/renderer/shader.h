//
// Created by jesse on 11/1/18.
//

#ifndef PIE_SHADER_H_H
#define PIE_SHADER_H_H

#include <string>

#include "lib/renderer/util/load_shader.h"

namespace pie {

/**
 * Program class for wrapping OpenGL shader program, which runs on the GPU
 */
class Program {
 public:
  explicit Program(const std::string &vs, const std::string &fs);
  ~Program() = default;

  // Getter
  GLuint program() const;

 private:
  GLuint program_;
};

/**
 * Shader class, pass this to objects to render. Can be shared between multiple objects which require the same
 * shader to run, to avoid multiple compilation of the same shader.
 */
class Shader {
 public:
  /**
   * @param vs Path to vertex shader
   * @param fs Path to fragment shader
   */
  explicit Shader(const std::string &vs, const std::string &fs);
  ~Shader() = default;

  //! Bind this shader to a drawable object
  template<class T>
  void Bind(T& drawable) const {
    // Set vertex attribute pointers to the vertex data given in the shaders
    // Ugly cast to void* needed because of the OpenGL API
    glVertexAttribPointer(vpos_loc_, 3, GL_FLOAT, GL_FALSE, drawable.stride(), (void*)drawable.vertex_offset());
    glEnableVertexAttribArray(vpos_loc_); // vpos_location_
    glVertexAttribPointer(vcol_loc_, 3, GL_FLOAT, GL_FALSE, drawable.stride(), (void*)drawable.color_offset());
    glEnableVertexAttribArray(vcol_loc_); // vcol_location_
    glVertexAttribPointer(vtex_loc_, 2, GL_FLOAT, GL_FALSE, drawable.stride(), (void*)drawable.texture_offset());
    glEnableVertexAttribArray(vtex_loc_);
  }

  /**
   * @brief Use the shader in the rendering loop
   * @param mvp The model-view-projection matrix data
   */
  void Use(const float *mvp) const;

 private:
  //! Compile the shader, return OpenGL program
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
