#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/draw/drawable.h"

using namespace pie;

int main() {
  Renderer renderer(600, 480);
  renderer.AddObject(std::shared_ptr<Drawable<GLFWwindow>>(new Square(-0.5, -0.5, 0.2)));
  renderer.AddObject(std::shared_ptr<Drawable<GLFWwindow>>(new Square(0.5, 0.5, 0.3)));
  renderer.Loop();
  return 0;
}

