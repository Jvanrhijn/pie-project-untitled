//#inclu
// Created by jesse on 11/16/18.
//

#include "src/game_tile.h"

namespace pie {

constexpr Color GameTile::highlight_color_;
constexpr Color GameTile::current_highlight_color_;

GameTile::GameTile(std::shared_ptr<pie::Tile> tile,
                   std::shared_ptr<pie::Square> square,
                   std::shared_ptr<pie::String> string)
  : tile_(std::move(tile)), square_(std::move(square)), string_(std::move(string))
{}

void GameTile::SetText(String string) {
  *string_ = std::move(string);
  double x, y;
  std::tie(x, y) = square_->location();
  string_->MoveTo(x, y);
  string_->Center();
}

void GameTile::ReachableHighlight() {
  square_->Color(highlight_color_);
}

void GameTile::ResetHighlight() {
  square_->Color(Color{1.0, 1.0, 1.0});
}

void GameTile::CurrentHighlight() {
  square_->Color(current_highlight_color_);
}

std::pair<size_t, size_t> GameTile::coordinates() const {
  return tile_->coordinates();
}

inp::Position<double> GameTile::position() const {
  double x, y;
  std::tie(x, y) = square_->location();
  return inp::Position<double>{x, y};
}

std::vector<std::shared_ptr<Tile>> GameTile::reachables() const {
  return tile_->reachables();
}

std::shared_ptr<Tile> GameTile::tile() const {
  return tile_;
}

std::shared_ptr<Square> GameTile::square() const {
  return square_;
}

std::shared_ptr<String> GameTile::string() const {
  return string_;
}


} // namespace pie

