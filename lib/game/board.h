//
// Created by jesse on 10/22/18.
//

#ifndef __PIE_SRC_BOARD_H
#define __PIE_SRC_BOARD_H

#include <memory>

#include "grid.h"
#include "tile.h"
#include "renderer/drawable.h"

namespace pie {

class Board {
 public:
  explicit Board(size_t side);

  Board(const Board &other);

  //! Retrieves a pointer to the tile located at (row, col)
  std::shared_ptr<Tile> GetTile(size_t row, size_t col);

  // Getters
  size_t side() const;

 private:
  SquareGrid<std::shared_ptr<Tile>> tiles_;
  size_t side_;

};

} // namespace pie
#endif //PIE_BOARD_H
