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
  // set OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
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
  // setup viewport
  glViewport(0, 0, width_, height_);
  // OpenGL options
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // Set keypress callbacks
  SetKeyCallbacks();
}

Renderer::~Renderer() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void Renderer::AddObject(std::shared_ptr<pie::Drawable<GLFWwindow>> object) {
  objects_.push_back(std::move(object));
}

void Renderer::Loop() const {
  while(!glfwWindowShouldClose(window_)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
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

void Renderer::DrawObject(const Drawable<GLFWwindow>& object) const {
  object.Draw(window_);
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
