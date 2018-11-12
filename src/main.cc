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
      std::shared_ptr<Drawable<GLFWwindow>> object = std::make_shared<Square>(x, y, 0.95*width, tex, shader);
      renderer.AddObject(object);
    }
  }
}


int main() {

  Renderer renderer(900, 900);

  Texture marble("textures/marble.jpg");

  Shader<GL_VERTEX_SHADER> vertex_shader("lib/renderer/shaders/square.vs");
  Shader<GL_FRAGMENT_SHADER> fragment_shader("lib/renderer/shaders/square.fs");
  VFShader square_shader(vertex_shader, fragment_shader);

  auto char_map = getCharMap("lib/renderer/fonts/arial.ttf", 48, Color{0.0, 0.0, 0.0});
  std::shared_ptr<Drawable<GLFWwindow>> character = std::make_shared<Character>(char_map.at('c'));

  grid(10, marble, square_shader, renderer);

  std::shared_ptr<Drawable<GLFWwindow>> string = std::make_shared<String>("A test string", char_map, 1.5f);
  auto c = char_map.at('L');
  std::shared_ptr<Drawable<GLFWwindow>> char_p = std::make_shared<Character>(c);

  renderer.AddObject(string);
  string->MoveTo(0.5f, 0.5f);

  renderer.Loop();

  return EXIT_SUCCESS;
}

