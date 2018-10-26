//
// Created by jesse on 10/25/18.
//

#ifndef __PIE_SRC_RULES_H
#define __PIE_SRC_RULES_H

#include "src/board.h"
#include "src/tile.h"

#include "util/functions.h"

#include "lib/optional.h"

namespace pie {

class Rules {
 public:
  Rules(size_t board_side, size_t start_row, size_t start_col);

  Optional<std::shared_ptr<Tile>> MoveTo(size_t row, size_t col);

  std::shared_ptr<Tile> current_tile() const;

 private:
  void SetTileReachables(std::shared_ptr<Tile> tile);

 private:
  Board board_;
  std::shared_ptr<Tile> current_tile_;

  // Tiles that are skipped in a move
  static constexpr size_t straight_move_spacing_{2};
  static constexpr size_t diagonal_move_spacing_{1};
};

} // namespace pie

#endif // __PIE_SRC_RULES_H
