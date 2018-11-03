//
// Created by jesse on 11/1/18.
//
#include "lib/renderer/shader.h"

namespace pie {

Program::Program(const std::string &vs, const std::string &fs)
  : program_(loadShaders(vs.c_str(), fs.c_str()))
{}

GLuint Program::program() const {
  return program_;
}

Shader::Shader(const std::string &vs, const std::string &fs)
  : vs_(vs), fs_(fs), program_(CompileShader()),
    mvp_loc_(glGetUniformLocation(program_.program(), "MVP")),
    vpos_loc_(glGetAttribLocation(program_.program(), "vPos")),
    vcol_loc_(glGetAttribLocation(program_.program(), "vCol")),
    vtex_loc_(glGetAttribLocation(program_.program(), "vTex"))

{}

void Shader::Use(const float *mvp) const {
  glUseProgram(program_.program());
  // perform transformations
  glUniformMatrix4fv(mvp_loc_, 1, GL_FALSE, (const GLfloat*) mvp);
}

Program Shader::CompileShader() {
  return Program(vs_, fs_);
}

} // namespace pie

