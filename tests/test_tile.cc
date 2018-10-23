//
// Created by Guthorak on 10/22/18.
//

#include "gtest/gtest.h"
#include "tile.h"

TEST(TestTile, Constructor) {
  size_t row = 1;
  size_t column = 2;
  pie::Tile test_tile(row, column);
  ASSERT_EQ(test_tile.coordinates(), std::make_pair(row, column));
}

TEST(TestTile, SetAndValue) {
  pie::Tile tile(1, 2);
  ASSERT_FALSE(tile.IsSet());

  tile.set_value(5);
  ASSERT_TRUE(tile.IsSet());

  ASSERT_EQ(tile.value(), 5);
}
