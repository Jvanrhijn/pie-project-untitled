#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/renderer/drawable.h"
#include "lib/renderer/texture.h"
#include "lib/renderer/text/character.h"
#include "lib/renderer/text/charmap.h"
#include "lib/renderer/text/string.h"
#include "lib/input/input.h"

#include "src/game.h"

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

  try {
    Game game{1, 3, 10, 900, 900};
    game.RenderLoop();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return EXIT_SUCCESS;
}

