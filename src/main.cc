#include "src/game.h"
#include "lib/argparse/argparse.h"


constexpr int rdefault = 0;
constexpr int cdefault = 0;
constexpr int side_default = 5;
constexpr int width_default = 600;
constexpr bool autosolve_default = false;


int main(int argc, char *argv[]) {
  // retrieve command line arguments
  pie::ArgParser argparser(argc, argv);
  int r = argparser.GetArg("r", rdefault);
  int c = argparser.GetArg("c", cdefault);
  int side = argparser.GetArg("n", side_default);
  int width = argparser.GetArg("w", width_default);
  bool autosolve = argparser.GetArg("a", autosolve_default);

  // ghetto user input validation
  if (r < 0 || c < 0 || side <= 0 || width <= 0) {
    throw std::runtime_error("All command line parameters must be non-negative");
  }

  try {
    if (!autosolve) {
      pie::Game game(r, c, side, width);
      game.RenderLoop();
    } else {
      pie::Rules rules(side, r, c);
      rules.MoveTo(2, 2);
      rules.MoveTo(4, 4);
      rules.MoveTo(1, 4);
      pie::Game game(width, rules);
      game.RenderLoop();
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
