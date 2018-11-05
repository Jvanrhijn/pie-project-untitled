#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/draw/drawable.h"
#include "lib/renderer/texture.h"

using namespace pie;

int main() {
  Renderer renderer(1600, 900);

  Texture paper("textures/paper.jpg");
  Texture wall("textures/wall.jpg");
  Texture container("textures/container.jpg");

  Shader<GL_VERTEX_SHADER> vertex_shader("lib/renderer/shaders/vertex_shader_test.vs");
  Shader<GL_FRAGMENT_SHADER> fragment_shader("lib/renderer/shaders/fragment_shader_test.fs");
  ShaderPipeline<decltype(vertex_shader), decltype(fragment_shader)> square_shader(vertex_shader, fragment_shader);

  renderer.AddObject(std::shared_ptr<Drawable<GLFWwindow>>(new Square(-0.5, -0.5,  0.4, paper, square_shader)));
  renderer.AddObject(std::shared_ptr<Drawable<GLFWwindow>>(new Square( 0.5, -0.5,  0.4, paper, square_shader)));
  renderer.AddObject(std::shared_ptr<Drawable<GLFWwindow>>(new Square(-0.5,  0.5,  0.4, paper, square_shader)));
  renderer.AddObject(std::shared_ptr<Drawable<GLFWwindow>>(new Square( 0.5,  0.5,  0.4, paper, square_shader)));

  renderer.Loop();
  return 0;
}

