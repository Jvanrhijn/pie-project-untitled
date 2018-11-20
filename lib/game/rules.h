//
// Created by jesse on 10/25/18.
//

#ifndef __PIE_SRC_RULES_H
#define __PIE_SRC_RULES_H

#include "board.h"
#include "tile.h"

#include "optional.h"

namespace pie {

class Rules {
 public:
  Rules(size_t board_side, size_t start_row, size_t start_col);

  Rules(const Rules &rules);

  /**
   * @brief Attempt move to the tile located at (row, column)
   * returns empty Optional if the move is not allows, otherwise Optional containing
   * the moved-to tile
  */
  Optional<std::shared_ptr<Tile>> MoveTo(size_t row, size_t col);

  //! Returns true if the board is in a finished state, i.e. each square is occupied
  bool Finished() const;

  // getters
  std::shared_ptr<Tile> current_tile() const;
  const Board& board() const;
  Board& board();

 private:
  //! Construct the reachable tiles for the passed argument and set them
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
