//
// Created by jesse on 10/22/18.
//
#include "board.h"

namespace pie {

Board::Board(size_t side)
  : tiles_(side)
{
  // TODO create tiles with appropriate coordinates and reachable neighbors
  for (size_t row=0; row<side; row++) {
    for (size_t col=0; col<side; col++) {
      tiles_.Set(row, col, Tile(row, col));
    }
  }
}

const Tile& Board::GetTile(size_t row, size_t col) const {
  return tiles_.Get(row, col);
}

} // namespace pie

