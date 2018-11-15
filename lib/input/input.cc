//
// Created by jesse on 11/14/18.
//
#include "lib/input/input.h"
#include <iostream>

namespace inp {

Mouse::Mouse(GLFWwindow *window)
  : window_(window)
{
  glfwSetWindowUserPointer(window, this);
  glfwSetMouseButtonCallback(window, [](GLFWwindow *w, int b, int a, int m) {
    if (b == GLFW_MOUSE_BUTTON_LEFT && a == GLFW_PRESS) {
      auto *p = glfwGetWindowUserPointer(w);
      auto pos = static_cast<Mouse *>(p)->GetPosition();
      std::cout << pos.x << " " << pos.y << std::endl;
    }
  });
}

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

