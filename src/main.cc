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

  renderer.AddObject(std::shared_ptr<Drawable<GLFWwindow>>(new Square(0.0, 0.2, 0.2, wall)));
  renderer.AddObject(std::shared_ptr<Drawable<GLFWwindow>>(new Square(0.5, 0.5, 0.3, paper)));
  renderer.AddObject(std::shared_ptr<Drawable<GLFWwindow>>(new Square(-0.5, -0.5, 0.2, container)));

  renderer.Loop();
  return 0;
}

