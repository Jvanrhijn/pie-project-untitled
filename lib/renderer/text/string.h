//
// Created by jesse on 11/10/18.
//

#ifndef PIE_STRING_H
#define PIE_STRING_H

#include <string>
#include <algorithm>

#include "lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "lib/renderer/drawable.h"
#include "lib/renderer/text/charmap.h"
#include "lib/renderer/text/character.h"

namespace pie {

class String : public Drawable<GLFWwindow> {
 public:
  String(std::string text, const charmap& char_map, float scale=1.0f);

  void Center();

  void Draw(GLFWwindow*) const override;

  void MoveTo(double x, double y) override;

  void MoveAlong(double dx, double dy) override;

  void Rotate(double angle) override;

 private:
  std::string text_;
  std::pair<float, float> location_;

  std::vector<Character> characters_;

  float scale_;

};

} // namespace pie

#endif //PIE_STRING_H
