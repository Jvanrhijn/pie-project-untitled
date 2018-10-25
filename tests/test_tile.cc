//
// Created by Guthorak on 10/22/18.
//

#include "gtest/gtest.h"
#include "src/tile.h"

TEST(TestTile, Constructor) {
  size_t row = 1; //arbitrary row value
  size_t column = 2; //arbitrary column value
  pie::Tile test_tile(row, column);
  ASSERT_EQ(test_tile.coordinates(), std::make_pair(row, column));
}

TEST(TestTile, SetAndTestValue) {
  pie::Tile tile(1, 2);
  ASSERT_FALSE(tile.IsSet());

  size_t value(5); //arbitrary value
  tile.set_value(value);
  ASSERT_TRUE(tile.IsSet());

  ASSERT_EQ(tile.value(), value);
}

TEST(TestTile, SetAndTestCordinates){
  pie::Tile undefined_tile;
  size_t row = 4; //arbitrary row value
  size_t col = 6; //arbitrary column value
  undefined_tile.set_coordinates(row, col);

  ASSERT_EQ(undefined_tile.coordinates(), std::make_pair(row, col));

  pie::Tile defined_tile(row, col);

  ASSERT_EQ(undefined_tile.coordinates(), defined_tile.coordinates());
}
