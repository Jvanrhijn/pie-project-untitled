//
// Created by jesse on 10/22/18.
//
#include "board.h"

namespace pie {

Board::Board(size_t side)
  : tiles_(side), side_(side)
{
  // TODO create tiles with appropriate coordinates and reachable neighbors
  for (size_t row=0; row<side; row++) {
    for (size_t col=0; col<side; col++) {
      tiles_.Set(row, col, std::make_shared<Tile>(row, col));
    }
  }
}

std::shared_ptr<Tile> Board::GetTile(size_t row, size_t col) {
  return tiles_.Get(row, col);
}

size_t Board::side() const {
  return side_;
}

} // namespace pie

