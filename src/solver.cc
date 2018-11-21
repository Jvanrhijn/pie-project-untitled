//
// Created by Guthorak on 11/19/18.
//

#include "solver.h"

namespace pie {

Solver::Solver(const Rules& rules, size_t max_fails)
  : rules_(rules), initial_rules_(rules_), max_fails_(max_fails)
  {}


Rules Solver::Solve() {
  size_t counter = 0;
  while (!rules_.Finished())  {
    // creates a tile with the NextMove method of Solver, which is const since it won't be altered
    const auto tile = NextMove();
    // NextMove returns an optional, which is a tile with a value if there's a suitable tile to move to. If this is the
    // case, we move to that case. If this isn't the case, the board is reset to it's initial state and the the
    // process starts again until the board is completed or until it has started max_fails_ times.
    if (tile.has_value()) {
      size_t row, column;
      std::tie(row, column) = tile.value()->coordinates();
      rules_.MoveTo(row, column);
    } else {
      if (++counter > max_fails_) {
        break;
      }
      rules_ = Rules(initial_rules_);
    }
  }
  return rules_;
}


Optional<std::shared_ptr<Tile>> Solver::NextMove() {
  using tile_pair = std::pair<std::shared_ptr<Tile>, size_t>;
  auto tile = rules_.current_tile();
  std::vector<tile_pair> possible_moves;
  // We don't want to copy the reachables of the tile, and we don't want to change them, so r is a reference to a
  // reachable of tile which is constant.
  for (const auto& r: tile ->reachables()) {
    if (!r->IsSet()) {
      size_t num_reachable = 0;
      // Look at the reachables of r, called rr, which we don't want to copy or change, so it's  a constant reference.
      // We then count the amount of reachables each r has.
      for (const auto& rr: r->reachables()) {
        num_reachable += rr->IsSet()? 0 : 1;
      }
      possible_moves.emplace_back(r, num_reachable);
    }
  }
  // Account for the possibility that the tile might have no valid reachables by using Optional
  if (possible_moves.empty()) {
    return Optional<std::shared_ptr<Tile>>();
  }
  std::sort(possible_moves.begin(), possible_moves.end(),
      [](tile_pair x, tile_pair y) {
    return x.second < y.second;
  });
  std::vector<tile_pair> equivalent_moves;
  std::copy_if (possible_moves.begin(), possible_moves.end(), std::back_inserter(equivalent_moves),
      [&possible_moves](tile_pair x) {
    return x.second == possible_moves[0].second;
  });
  std::uniform_int_distribution<size_t> distribution(0, equivalent_moves.size()-1);
  return equivalent_moves[distribution(generator_)].first;
}


} //namespace pie
