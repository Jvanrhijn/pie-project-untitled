#include "lib/renderer/util/load_shader.h"

/*
 * Code adapted from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
 */

namespace pie {

void loadShader(const char *shader_path, GLuint shader_type, GLuint &program) {
  // create shader
  GLuint shader_id = glCreateShader(shader_type);

  // read shader code from file
  std::string shader_code;
  std::ifstream shader_stream(shader_path, std::ios::in);
  if (shader_stream.is_open()) {
    std::stringstream sstr;
    sstr << shader_stream.rdbuf();
    shader_code = sstr.str();
    shader_stream.close();
  } else {
    std::cerr << "Unable to open " << shader_path << ", are you in the right directory?" << std::endl;
  }

  GLint result = GL_FALSE;
  std::clog << "Compiling shader " << shader_path << std::endl;
  const char *source_pointer = shader_code.c_str();
  glShaderSource(shader_id, 1, &source_pointer, nullptr);
  glCompileShader(shader_id);

  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
  if (!result) {
    int info_log_length;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    std::vector<char> err_msg(info_log_length + 1);
    glGetShaderInfoLog(shader_id, info_log_length, nullptr, &err_msg[0]);
    std::cerr << "Shader compilation failed: " << err_msg[0] << std::endl;
  }

  // attach program
  glAttachShader(program, shader_id);
  glDeleteShader(shader_id);
}

}
