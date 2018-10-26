//
// Created by jesse on 10/25/18.
//

#include "src/rules.h"

namespace pie {

Rules::Rules(size_t side, size_t start_row, size_t start_col)
: board_(Board(side)), current_tile_(std::make_shared<Tile>(board_.GetTile(start_row, start_col)))
{
  // TODO assign reachable tiles to each tile
  for (size_t i=0; i<side; i++) {
    for (size_t j=0; j<side; j++) {
      auto& tile = board_.GetTile(i, j);
      //tile->add_reachable(board_.GetTile(i-2, j);
      tile.set_coordinates(0, 0);
    }
  }
}

std::shared_ptr<Tile> Rules::current_tile() const {
  return current_tile_;
}

Optional<std::shared_ptr<Tile>> Rules::MoveTo(size_t row, size_t col) {
  auto new_coordinates = std::make_pair(row, col);
  auto reachables = current_tile_->reachables();
  for (const auto& r: reachables) {
    if (r->coordinates() == new_coordinates) {
      return r;
    }
  }
  return Optional<std::shared_ptr<Tile>>();
}

} // namespace pie

