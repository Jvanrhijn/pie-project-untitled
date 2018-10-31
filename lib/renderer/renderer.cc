//
// Created by jesse on 10/30/18.
//
#include "lib/renderer/renderer.h"

namespace pie {

Renderer::Renderer(size_t width, size_t height)
  : width_(width), height_(height)
{
  // Initialize GLFW
  if(!glfwInit()) {
    exit(ExitCode::FAIL_OPENGL_INIT);
  }
  if (!(window_ = glfwCreateWindow(width, height, "Game", nullptr, nullptr))) {
    exit(ExitCode::FAIL_WINDOW_CREATE);
  }
  // Output errors to stderr
  glfwMakeContextCurrent(window_);
  if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    exit(ExitCode::FAIL_LOAD_GL);
  }
  glfwSwapInterval(1);
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

void Renderer::AddObject(std::shared_ptr<pie::Drawable> object) {
  objects_.push_back(std::move(object));
}

void Renderer::Loop() const {
  while(!glfwWindowShouldClose(window_)) {
    glViewport(0, 0, width_, height_);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (const auto& obj: objects_) {
      DrawObject(*obj);
    }
    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}

GLFWwindow *Renderer::window() const {
  return window_;
}

void Renderer::DrawObject(const Drawable& object) const {
  object.Draw();
}

void Renderer::SetKeyCallbacks() {
  // Close the window on ESC or Q
  glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int, int, int) {
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  });
}

}
