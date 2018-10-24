//
// Created by jesse on 10/22/18.
//

#ifndef __PIE_SRC_BOARD_H
#define __PIE_SRC_BOARD_H

#include <memory>

#include "../lib/grid.h"
#include "tile.h"

namespace pie {

class Board {
 public:
  explicit Board(size_t side);

  //! Get the value of the active tile
  size_t CurrentValue() const;

  //! Move to a new tile if possible
  void MoveTo(size_t row, size_t col);

 private:
  SquareGrid<Tile> tiles_;
  std::shared_ptr<Tile> current_tile_;

};

} // namespace pie
#endif //PIE_BOARD_H
