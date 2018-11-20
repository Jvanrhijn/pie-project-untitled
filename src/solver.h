//
// Created by Guthorak on 11/19/18.
//

#ifndef PIE_SOLVER_H
#define PIE_SOLVER_H

#include <random>
#include "lib/game/rules.h"
#include "lib/optional.h"

namespace pie {

class Solver {
 public:
  explicit Solver(const Rules& rules, size_t max_fails);
  Rules Solve();

 private:
  Optional<std::shared_ptr<Tile>> NextMove() const ;

 private:
  Rules rules_;
  Rules initial_rules_;
  size_t max_fails_;

};





} // end namespace pie

#endif //PIE_SOLVER_H
