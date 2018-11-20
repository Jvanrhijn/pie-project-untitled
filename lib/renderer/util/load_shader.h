//
// Created by jesse on 10/31/18.
//

#ifndef __PIE_LIB_RENDERER_UTIL_LOAD_SHADER_H
#define __PIE_LIB_RENDERER_UTIL_LOAD_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "../exceptions.h"
#include "glad.h"
#include <GLFW/glfw3.h>

namespace pie {

void loadShader(const char *, GLuint, GLuint&);

GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);

} // namespace pie

#endif // __PIE_LIB_RENDERER_UTIL_LOAD_SHADER_H
