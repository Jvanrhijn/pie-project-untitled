#include "src/game.h"


int main() {
  try {
    pie::Game game{1, 1, 5, 600};
    game.RenderLoop();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
