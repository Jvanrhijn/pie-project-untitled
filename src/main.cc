#include "src/game.h"
#include "lib/argparse/argparse.h"


constexpr int xdefault = 0;
constexpr int ydefault = 0;
constexpr int side_default = 5;
constexpr int width_default = 600;


int main(int argc, char *argv[]) {
  // retrieve command line arguments
  pie::ArgParser argparser(argc, argv);
  int x = argparser.GetArg("x", xdefault);
  int y = argparser.GetArg("y", ydefault);
  int side = argparser.GetArg("n", side_default);
  int width = argparser.GetArg("w", width_default);

  // ghetto user input validation
  if (x < 0 || y < 0 || side <= 0 || width <= 0) {
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
