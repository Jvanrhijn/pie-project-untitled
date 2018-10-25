//
// Created by Guthorak on 10/22/18.
//

#include <tuple>
#include "src/tile.h"

namespace pie {

Tile::Tile(size_t row, size_t column)
: coordinates_(std::make_pair(row, column)){
}

bool Tile::IsSet() const {
  return value_.has_value();
}

const std::pair<size_t, size_t> &Tile::coordinates() const {
  return coordinates_;
}

const Optional<size_t> &Tile::value() const {
  return value_;
}

const std::vector<std::shared_ptr<Tile>> &Tile::reachables() const {
  return reachables_;
}

void Tile::set_value(const size_t value) {
  Tile::value_ = value;
}

void Tile::set_coordinates(size_t x, size_t y) {
  coordinates_ = std::make_pair(x, y);
}

void Tile::add_reachable(std::shared_ptr<Tile> tile) {
  reachables_.push_back(std::move(tile));
}

} //namespace pie
