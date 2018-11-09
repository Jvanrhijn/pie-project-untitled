//
// Created by jesse on 11/8/18.
//

#ifndef __PIE_LIB_RENDERER_CHARACTER_H
#define __PIE_LIB_RENDERER_CHARACTER_H

#include "lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "lib/renderer/drawable.h"
#include "lib/renderer/fontface.h"
#include "lib/renderer/shader.h"
#include "lib/renderer/linmath.h"

namespace pie {

class Character : public Drawable<GLFWwindow> {
 public:
  Character(FontFace &face, char c, const VFShader &sp);
  ~Character() override = default;

  void Draw(GLFWwindow *window) const override;

  void MoveTo(double x, double y) override;
  void Rotate(double angle) override;

 private:
  void BuildVertices();

 private:
  VFShader shader_;

  GLuint tex_id_;
  GLuint advance_;
  std::pair<int, int> size_;
  std::pair<int, int> bearing_;

  std::pair<float, float> location_;

  // OpenGL vertex data
  static float vertex_data_[48];

  // vertex array object
  GLuint vao_;
  // vertex buffer object
  GLuint vbo_;
};

} // namespace pie

#endif //PIE_CHARACTER_H
