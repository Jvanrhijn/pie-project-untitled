//
// Created by jesse on 11/14/18.
//
#include "input.h"
#include <iostream>

namespace inp {

Mouse::Mouse(GLFWwindow *window)
  : window_(window)
{}

Position<double> Mouse::GetPosition() const {
  double x(0.0), y(0.0);
  if (window_) {
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    glfwGetCursorPos(window_, &x, &y);
    x = 2*x/width - 1.0;
    y = 1.0 - 2*y/height;
  }
  return Position<double>{x, y};
}

} // namespace inp

