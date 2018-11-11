//
// Created by jesse on 11/8/18.
//

#ifndef __PIE_LIB_RENDERER_CHARACTER_H
#define __PIE_LIB_RENDERER_CHARACTER_H

#include "lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "lib/renderer/drawable.h"
#include "lib/renderer/text/fontface.h"
#include "lib/renderer/shader.h"
#include "lib/renderer/linmath.h"

namespace pie {

class Character : public Drawable<GLFWwindow> {
 public:
  Character(FontFace &face, char c, const Color &color, const VFShader &sp);
  Character(const Character &) = default;
  ~Character() override = default;

  void Draw(GLFWwindow *window) const override;

  void MoveTo(double x, double y) override;
  void MoveAlong(double dx, double dy) override;
  void Rotate(double angle) override;

  //! Scale the text isotropically
  void Scale(float scale);

  // expose advance and location for string rendering
  GLuint advance() const;
  std::pair<float, float> location() const;

 private:
  void BuildVertices();

 private:
  VFShader shader_;

  float angle_;
  float scale_;

  Color color_;

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
