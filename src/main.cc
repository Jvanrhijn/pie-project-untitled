#include "src/game.h"
#include "lib/argparse/argparse.h"


int main(int argc, char *argv[]) {
  // retrieve command line arguments
  pie::ArgParser argparser(argc, argv);
  int x = argparser.GetArg("x", 0);
  int y = argparser.GetArg("y", 0);
  int side = argparser.GetArg("n", 5);
  int width = argparser.GetArg("w", 600);

  // ghetto user input validation
  if (x < 0 || y < 0 || side <= 0 < width <= 0) {
    throw std::runtime_error("All command line parameters must be non-negative");
  }

  try {
    pie::Game game(x, y, side, width);
    game.RenderLoop();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
