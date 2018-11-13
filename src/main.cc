#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/renderer/drawable.h"
#include "lib/renderer/texture.h"
#include "lib/renderer/text/character.h"
#include "lib/renderer/text/charmap.h"
#include "lib/renderer/text/string.h"

#include <map>
#include <thread>

#include <cstdlib>

using namespace pie;


template<class SP>
std::vector<std::shared_ptr<Square>> grid(int num_per_side, const Texture &tex, const SP &shader, Renderer &renderer) {
  std::vector<std::shared_ptr<Square>> out;
  double width = 2.0/num_per_side;
  for (int i=0; i<num_per_side; i++) {
    for (int j=0; j<num_per_side; j++) {
      double x = width*(j + 0.5) - 1.0;
      double y = width*(i + 0.5) - 1.0;
      auto object = std::make_shared<Square>(x, y, 0.95*width, tex, shader);
      out.push_back(object);
      object->Color(Color{1.0, 1.0, 1.0});
      renderer.AddObject(std::dynamic_pointer_cast<Drawable<GLFWwindow>>(object));
    }
  }
  return out;
}


int main() {

  Renderer renderer(900, 900);

  Texture marble("textures/marble.jpg");

  Shader<GL_VERTEX_SHADER> vertex_shader("lib/renderer/shaders/square.vs");
  Shader<GL_FRAGMENT_SHADER> fragment_shader("lib/renderer/shaders/square.fs");
  VFShader square_shader(vertex_shader, fragment_shader);

  auto char_map = getCharMap("lib/renderer/fonts/arial.ttf", 48, Color{0.0, 0.0, 0.0});

  auto squares = grid(5, marble, square_shader, renderer);
  squares[6]->Color(Color{1.0, 0.0, 0.0});

  std::shared_ptr<Drawable<GLFWwindow>> string = std::make_shared<String>("Hello, world!", char_map, 1.5f);

  renderer.AddObject(string);
  string->MoveTo(0.5f, 0.5f);

  renderer.Loop();

  return EXIT_SUCCESS;
}

