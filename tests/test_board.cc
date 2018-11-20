//
// Created by jesse on 10/25/18.
//

#include "gtest/gtest.h"
#include "game/board.h"

TEST(TestBoard, GetTile) {
  pie::Board board(5);
  size_t row = 2;
  size_t col = 2;
  auto tile = board.GetTile(row, col);
  ASSERT_EQ(tile->coordinates(), std::make_pair(row, col));
}
