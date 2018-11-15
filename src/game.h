//
// Created by jesse on 11/15/18.
//

#ifndef __PIE_SRC_GAME_H
#define __PIE_SRC_GAME_H

#include <cstddef>

#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/renderer/text/string.h"

#include "lib/input/input.h"

#include "lib/game/board.h"
#include "lib/game/tile.h"

#include "lib/grid.h"


namespace pie {

class Game {
 public:
  Game(std::size_t start_x, std::size_t start_y, std::size_t side, std::size_t width, std::size_t height);

 private:
  static constexpr size_t font_size{48};
  static constexpr double fill_factor{0.9};

  Renderer renderer_;
  inp::Mouse mouse_;
  Board board_;

  Grid<std::shared_ptr<Square>> squares_;
  Grid<std::shared_ptr<String>> text_;
};

} // namespace pie

#endif // __PIE_SRC_GAME_H
