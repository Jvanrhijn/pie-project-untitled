//
// Created by jesse on 11/1/18.
//

#ifndef PIE_SHADER_H_H
#define PIE_SHADER_H_H

#include <string>

#include "lib/renderer/util/load_shader.h"

namespace pie {

/**
 * Shader class, pass this to objects to render. Can be shared between multiple objects which require the same
 * shader to run, to avoid multiple compilation of the same shader.
 */
template<GLuint ShaderType>
class Shader {
 public:
  /**
   * @param shader_path Path to shader
   */
  explicit Shader(std::string shader_path)
    : shader_path_(std::move(shader_path))
  {}

  //! Type
  GLuint type() const {
    return ShaderType;
  }

  //! Getters
  const std::string& shader_path() const {
    return shader_path_;
  }

 private:
  std::string shader_path_;

};


template<class ...Shaders>
class ShaderPipeline {
 public:
  explicit ShaderPipeline(const Shaders& ...shaders)
    : program_(glCreateProgram())
  {
    // create program
    (void)std::initializer_list<int>{
      ((void)loadShader(shaders.shader_path().c_str(), shaders.type(), program_), 0)...
    };
    glLinkProgram(program_);
    // get shader attribute locations
    mvp_loc_= glGetUniformLocation(program_, "MVP");
    vpos_loc_ = glGetAttribLocation(program_, "vPos");
    vcol_loc_ = glGetAttribLocation(program_, "vCol");
    vtex_loc_ = glGetAttribLocation(program_, "vTex");
  }

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
  void Use(const float *mvp) const {
    glUseProgram(program_);
    // perform transformations
    glUniformMatrix4fv(mvp_loc_, 1, GL_FALSE, (const GLfloat*) mvp);
  }

 private:
  GLuint program_;

  GLuint mvp_loc_;
  GLuint vpos_loc_;
  GLuint vcol_loc_;
  GLuint vtex_loc_;

};

typedef ShaderPipeline<Shader<GL_VERTEX_SHADER>, Shader<GL_FRAGMENT_SHADER>> VSShader;

} // namespace pie

#endif //PIE_SHADER_H_H
