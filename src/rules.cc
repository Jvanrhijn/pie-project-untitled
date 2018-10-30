//
// Created by jesse on 10/25/18.
//

#include "src/rules.h"

namespace pie {

Rules::Rules(size_t side, size_t start_row, size_t start_col)
: board_(Board(side)), current_tile_(board_.GetTile(start_row, start_col))
{
  current_tile_->set_value(1);
  for (size_t i=0; i<side; i++) {
    for (size_t j=0; j<side; j++) {
      SetTileReachables(board_.GetTile(i, j));
    }
  }
}

std::shared_ptr<Tile> Rules::current_tile() const {
  return current_tile_;
}

const Board& Rules::board() const {
  return board_;
}

bool Rules::Finished() const {
  return *current_tile_->value() == board_.side()*board_.side();
}

Optional<std::shared_ptr<Tile>> Rules::MoveTo(size_t row, size_t col) {
  auto new_coordinates = std::make_pair(row, col);
  auto reachables = current_tile_->reachables();
  auto current_val = *current_tile_->value();
  for (const auto& r: reachables) {
    if (r->coordinates() == new_coordinates) {
      r->set_value(current_val+1);
      current_tile_ = r;
      return r;
    }
  }
  return Optional<std::shared_ptr<Tile>>();
}

void Rules::SetTileReachables(std::shared_ptr<Tile> tile) {
  size_t x, y;
  std::tie(x, y) = tile->coordinates();
  // since we store the coordinates as unsigned integers, we can abuse
  // overflow behaviour. We propose all eight possible moves. If the
  // x or y coordinates of the proposed moves are larger than the side
  // of the board, we reject the move. This works obviously for
  // moves that are on the east or south sides of the board, but due to the defined
  // behaviour of unsigned integer overflow it also works for moves on the north or west side.
  // This breaks when the side of the board or the move spacing approaches SIZE_T_MAX.
  std::vector<std::pair<size_t, size_t>> proposed_moves = {
      std::make_pair(x + straight_move_spacing_ + 1, y),
      std::make_pair(x - straight_move_spacing_ - 1, y),
      std::make_pair(x, y + straight_move_spacing_ + 1),
      std::make_pair(x, y - straight_move_spacing_ - 1),
      std::make_pair(x + diagonal_move_spacing_ + 1, y + diagonal_move_spacing_ + 1),
      std::make_pair(x - diagonal_move_spacing_ - 1, y - diagonal_move_spacing_ - 1),
      std::make_pair(x + diagonal_move_spacing_ + 1, y - diagonal_move_spacing_ - 1),
      std::make_pair(x - diagonal_move_spacing_ - 1, y + diagonal_move_spacing_ + 1)
  };
  for (const auto& pair: proposed_moves) {
    if (pair.first < board_.side() && pair.second < board_.side()) {
      tile->add_reachable(board_.GetTile(pair.first, pair.second));
    }
  }
}

} // namespace pie

