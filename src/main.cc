#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/renderer/drawable.h"
#include "lib/renderer/texture.h"
#include "lib/renderer/text/character.h"
#include "lib/renderer/text/charmap.h"
#include "lib/renderer/text/string.h"

#include <map>
#include <thread>

using namespace pie;


template<class SP>
void grid(int num_per_side, const Texture &tex, const SP &shader, Renderer &renderer) {
  double width = 2.0/num_per_side;
  for (int i=0; i<num_per_side; i++) {
    for (int j=0; j<num_per_side; j++) {
      double x = width*(j + 0.5) - 1.0;
      double y = width*(i + 0.5) - 1.0;
      std::shared_ptr<Drawable<GLFWwindow>> object = std::make_shared<Square>(x, y, 0.9*width, tex, shader);
      renderer.AddObject(object);
    }
  }
}


int main() {
  Renderer renderer(900, 900);

  Texture marble("textures/marble.jpg");

  Shader<GL_VERTEX_SHADER> vertex_shader("lib/renderer/shaders/vertex_shader_test.vs");
  Shader<GL_FRAGMENT_SHADER> fragment_shader("lib/renderer/shaders/fragment_shader_test.fs");
  VFShader square_shader(vertex_shader, fragment_shader);


  // construct charmap
  auto char_map = getCharMap("lib/renderer/fonts/arial.ttf", 48, Color{0.0, 0.0, 0.0});
  std::shared_ptr<Drawable<GLFWwindow>> character = std::make_shared<Character>(char_map.at('c'));

  grid(3, marble, square_shader, renderer);

  std::shared_ptr<Drawable<GLFWwindow>> string = std::make_shared<String>("Hello", char_map);

  renderer.AddObject(string);

  renderer.Loop();

  return EXIT_SUCCESS;
}

