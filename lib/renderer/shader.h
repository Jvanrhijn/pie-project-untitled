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
    // check if linking was successful
    int success;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    char info_log[512];
    if (!success) {
      glGetProgramInfoLog(program_, 512, nullptr, info_log);
      std::cerr << "Shader linking failed\n" << info_log << std::endl;
    }
    // get shader attribute locations
    mvp_loc_= glGetUniformLocation(program_, "MVP");
    vpos_loc_ = glGetAttribLocation(program_, "vPos");
    vcol_loc_ = glGetAttribLocation(program_, "vCol");
    vtex_loc_ = glGetAttribLocation(program_, "vTex");
  }

  template<class T>
  void Bind(const T& drawable) const {
    // Set vertex attribute pointers to the vertex data given in the shaders
    // Ugly cast to void* needed because of the OpenGL API
    if (vpos_loc_ >= 0) {
      glVertexAttribPointer(vpos_loc_, 3, GL_FLOAT, GL_FALSE, drawable.stride(), (void *) drawable.vertex_offset());
      glEnableVertexAttribArray(vpos_loc_);
    }
    if (vcol_loc_ >= 0) {
      glVertexAttribPointer(vcol_loc_, 3, GL_FLOAT, GL_FALSE, drawable.stride(), (void *) drawable.color_offset());
      glEnableVertexAttribArray(vcol_loc_);
    }
    if (vtex_loc_ >= 0) {
      glVertexAttribPointer(vtex_loc_, 2, GL_FLOAT, GL_FALSE, drawable.stride(), (void *) drawable.texture_offset());
      glEnableVertexAttribArray(vtex_loc_);
    }
  }

  /**
   * @brief Use the shader in the rendering loop
   * @param mvp The model-view-projection matrix data
   */
  void Use() const {
    glUseProgram(program_);
  }

  const GLuint &program() const {
    return program_;
  }

 private:
  GLuint program_;

  GLint mvp_loc_;
  GLint vpos_loc_;
  GLint vcol_loc_;
  GLint vtex_loc_;

};

typedef ShaderPipeline<Shader<GL_VERTEX_SHADER>, Shader<GL_FRAGMENT_SHADER>> VFShader;

} // namespace pie

#endif //PIE_SHADER_H_H
