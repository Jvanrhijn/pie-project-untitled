//
// Created by jesse on 10/30/18.
//
#include "lib/renderer/renderer.h"

namespace pie {

Renderer::Renderer(size_t width, size_t height) {
  // Initialize GLFW
  if(!glfwInit()) {
    exit(ExitCode::FAIL_OPENGL_INIT);
  }
  if (!(window_ = glfwCreateWindow(width, height, "Game", nullptr, nullptr))) {
    exit(ExitCode::FAIL_WINDOW_CREATE);
  }
  // Output errors to stderr
  glfwSetErrorCallback([](int err, const char* descr) {
    std::cerr << "GLFW ERROR " << err << ": " << descr << std::endl;
  });
  // Set keypress callbacks
  SetKeyCallbacks();
}

Renderer::~Renderer() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void Renderer::Loop() const {
  while(!glfwWindowShouldClose(window_)) {
    glfwPollEvents();
  }
}

GLFWwindow *Renderer::window() const {
  return window_;
}

void Renderer::DrawBoard(const pie::Board &board) const {
  // TODO implement Drawable on Board and Tile so we can render the game board
}

void Renderer::SetKeyCallbacks() {
  // Close the window on ESC or Q
  glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q && GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  });
}

}
