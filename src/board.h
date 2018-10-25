//
// Created by jesse on 10/22/18.
//

#ifndef __PIE_SRC_BOARD_H
#define __PIE_SRC_BOARD_H

#include <memory>

#include "lib/grid.h"
#include "src/tile.h"

namespace pie {

class Board {
 public:
  explicit Board(size_t side);

  //! Retrieves a reference to the tile located at (row, col)
  const Tile& GetTile(size_t row, size_t col) const;

 private:
  SquareGrid<Tile> tiles_;

};

} // namespace pie
#endif //PIE_BOARD_H
