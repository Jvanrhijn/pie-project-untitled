//
// Created by jesse on 11/16/18.
//

#ifndef PIE_GAME_TILE_H
#define PIE_GAME_TILE_H

#include <memory>

#include "lib/renderer/square.h"
#include "lib/renderer/text/string.h"
#include "lib/game/tile.h"
#include "lib/input/input.h"

namespace pie {

class GameTile {
 public:
  GameTile(std::shared_ptr<Tile>, std::shared_ptr<Square>, std::shared_ptr<String>);

  GameTile() = default;

  void SetText(String);

  void Highlight();

  void ResetHighlight();

  void CurrentHighlight();

  //! Getters
  std::shared_ptr<Tile> tile() const;
  std::shared_ptr<Square> square() const;
  std::shared_ptr<String> string() const;

  std::pair<size_t, size_t> coordinates() const;
  inp::Position<double> position() const;
  std::vector<std::shared_ptr<Tile>> reachables() const;

 private:
  std::shared_ptr<Tile> tile_;
  std::shared_ptr<Square> square_;
  std::shared_ptr<String> string_;

  static constexpr Color highlight_color_{0.0, 1.0, 0.0};

};

} // namespace pie

#endif //PIE_GAME_TILE_H