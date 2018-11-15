//
// Created by jesse on 11/1/18.
//

#ifndef __PIE_LIB_RENDER_TEXTURE_H
#define __PIE_LIB_RENDER_TEXTURE_H

#include <string>
#include <iostream>


#include "lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "exceptions.h"

namespace pie {

class Texture {
 public:
  Texture() = default;
  explicit Texture(const char *data);

  // Don't want texture to be copyable -- huge overhead
  Texture(const Texture&) = delete;

  ~Texture() = default;

  // getters
  GLuint texture_id() const;

 private:
  GLuint texture_id_;
  int width_;
  int height_;
  int num_channels_;
};

} // namespace pie

#endif //PIE_TEXTURE_H
