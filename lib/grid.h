//
// Created by jesse on 10/22/18.
//

#include <vector>

#ifndef __PIE_SRC_GRID_H
#define __PIE_SRC_GRID_H


namespace pie {

//! Convenience class for keeping a 2D grid of values
template<class T>
class Grid {
 public:
  Grid(size_t rows, size_t columns)
      : data_(std::vector<std::vector<T>>(rows, std::vector<T>(columns))), rows_(rows), columns_(columns)
  {}

  //! Set the value of a point in the grid at (row, column)
  void Set(size_t row, size_t col, const T &value) {
    data_[row][col] = value;
  }

  //! Get a mutable reference to the element of the grid at (row, column)
  T &Get(size_t row, size_t col) {
    // We don't care much about accessor performance right now
    return data_.at(row).at(col);
  }

  // Getters

  // not const because that actually adds overhead
  size_t rows() const {
    return rows_;
  }

  size_t columns() const {
    return columns_;
  }

 private:
  std::vector<std::vector<T>> data_;
  size_t rows_;
  size_t columns_;

};

// Simple specialization for a square grid type
template<class T>
class SquareGrid : public Grid<T> {
 public:
  explicit SquareGrid(size_t side)
      : Grid<T>(side, side) {}
};

} // namespace pie

#endif //__PIE_SRC_GRID_H

