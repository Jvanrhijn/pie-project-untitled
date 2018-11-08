//
// Created by jesse on 11/8/18.
//

#ifndef __PIE_LIB_RENDERER_CHARACTER_H
#define __PIE_LIB_RENDERER_CHARACTER_H

#include <GLFW/glfw3.h>

#include "lib/renderer/drawable.h"
#include "lib/renderer/fontface.h"
#include "lib/renderer/linmath.h"

namespace pie {

class Character : public Drawable<GLFWwindow> {
 public:
  Character(FontFace &face, char c);
  ~Character() override = default;

  void Draw(GLFWwindow *window) const override;

 private:
  char c_;

  GLuint tex_id_;
  GLuint advance_;
  std::pair<int, int> size_;
  std::pair<int, int> bearing_;

};

} // namespace pie

#endif //PIE_CHARACTER_H
