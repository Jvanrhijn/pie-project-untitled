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

int main() {

  try {
    Game game{2, 2, 5, 600};
    game.RenderLoop();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

