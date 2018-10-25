//
// Created by jesse on 10/25/18.
//

#include "gtest/gtest.h"
#include "src/rules.h"

TEST(TestRules, Construct) {
  size_t side = 10;
  size_t x = 5;
  size_t y = 5;
  pie::Rules rules(side, x, y);
  auto tile = rules.current_tile();
  ASSERT_EQ(tile->coordinates(), std::make_pair(x, y));
}

TEST(TestRules, MoveTo) {
  size_t side = 10;
  size_t x = 5;
  size_t y = 5;
  pie::Rules rules(side, x, y);
  auto new_tile = rules.MoveTo(8, 5);
  auto new_tile_invalid = rules.MoveTo(5, 6);
  ASSERT_FALSE(new_tile_invalid.has_value());
  ASSERT_EQ((*new_tile)->coordinates(), std::make_pair(8ul, 5ul));
}