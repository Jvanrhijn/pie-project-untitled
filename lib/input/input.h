//
// Created by jesse on 11/14/18.
//

#ifndef __PIE_LIB_INPUT_INPUT_H
#define __PIE_LIB_INPUT_INPUT_H

#include "lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

namespace inp {

template<class T>
struct Position {
  Position(T x, T y) : x(x), y(y) {}
  T x;
  T y;
};

class Mouse {
 public:
  explicit Mouse(GLFWwindow *window);

  static void MouseClickCallback(GLFWwindow *, int, int, int);

  Position<double> GetPosition() const;

 private:
  GLFWwindow *window_;


};

} // namespace inp

#endif //
