#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/draw/drawable.h"
#include "lib/renderer/texture.h"

using namespace pie;

int main() {
  Renderer renderer(1600, 900);
  Texture tile_tex("textures/paper.jpg");
  Texture tile_tex_wall("textures/wall.jpg");
  renderer.AddObject(std::shared_ptr<Drawable<GLFWwindow>>(new Square(-0.0, -0.0, 0.2, tile_tex_wall)));
  renderer.AddObject(std::shared_ptr<Drawable<GLFWwindow>>(new Square(0.5, 0.5, 0.3, tile_tex)));
  renderer.Loop();
  return 0;
}

