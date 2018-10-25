//
// Created by jesse on 10/22/18.
//
#include "gtest/gtest.h"
#include "lib/grid.h"


TEST(TestGrid, Construct) {
  pie::Grid<int> g(3, 2);
  ASSERT_EQ(g.rows(), 3);
  ASSERT_EQ(g.columns(), 2);
}

TEST(TestGrid, SetData) {
  size_t rows = 3;
  size_t cols = 2;
  pie::Grid<int> g(rows, cols);
  g.Set(0, 0, 1);
  g.Set(0, 1, 2);
  g.Set(1, 0, 3);
  g.Set(1, 1, 4);
  g.Set(2, 0, 5);
  g.Set(2, 1, 6);
  int num = 1;
  for (size_t i=0; i<rows; i++) {
    for (size_t j=0; j<cols; j++) {
      ASSERT_EQ(g.Get(i, j), num);
      num++;
    }
  }
}

TEST(TestGrid, OutOfBounds) {
  pie::Grid<int> g(0, 0);
  ASSERT_ANY_THROW(g.Get(0, 0));
}

TEST(TestGrid, SquareGrid) {
  pie::SquareGrid<int> g(5);
  g.Set(2, 2, 1);
  ASSERT_EQ(g.Get(2, 2), 1);
}
