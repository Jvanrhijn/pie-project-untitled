#include "game.h"
#include "solver.h"
#include "argparse/argparse.h"


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
  } else if (r >= side || c >= side) {
    throw std::runtime_error("Starting row and column must be less than the number of squares per side");
  }

  try {
    if (!autosolve) {
      pie::Game game(r, c, side, width);
      game.RenderLoop();
    } else {
      pie::Solver solver(pie::Rules(side, r, c), 10);
      pie::Game game(width, solver.Solve());
      game.RenderLoop();
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
