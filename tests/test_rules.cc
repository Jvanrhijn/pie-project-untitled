//
// Created by jesse on 10/25/18.
//

#include "gtest/gtest.h"
#include "game/rules.h"

#include "../util/functions.h"

TEST(TestRules, Construct) {
  size_t side = 10;
  size_t x = 5;
  size_t y = 5;
  pie::Rules rules(side, x, y);
  auto tile = rules.current_tile();
  ASSERT_EQ(tile->coordinates(), std::make_pair(x, y));
}

TEST(TestRules, ReachablesCenter) {
  size_t side = 10;
  size_t x = 5;
  size_t y = 5;
  pie::Rules rules(side, x , y);

  auto reachables = rules.current_tile()->reachables();
  ASSERT_EQ(reachables.size(), 8ul);
  std::vector<std::pair<size_t, size_t>> coordinates{
    std::make_pair(8ul, 5ul),
    std::make_pair(2ul, 5ul),
    std::make_pair(5ul, 2ul),
    std::make_pair(5ul, 8ul),
    std::make_pair(7ul, 7ul),
    std::make_pair(3ul, 3ul),
    std::make_pair(7ul, 3ul),
    std::make_pair(3ul, 7ul)
  };
  for (const auto& r: reachables) {
    ASSERT_TRUE(pie::contains(coordinates, r->coordinates()));
  }
}

TEST(TestRules, ReachablesCorner) {
  size_t side = 10;
  size_t x = 0;
  size_t y = 0;
  pie::Rules rules(side, x, y);

  auto reachables = rules.current_tile()->reachables();
  ASSERT_EQ(reachables.size(), 3);
  std::vector<std::pair<size_t, size_t>> coordinates{
    std::make_pair(3ul, 0),
    std::make_pair(0, 3ul),
    std::make_pair(2ul, 2ul)
  };
  for (const auto& r: reachables) {
    ASSERT_TRUE(pie::contains(coordinates, r->coordinates()));
  }
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
  ASSERT_EQ(rules.current_tile(), *new_tile); // test for correctly updated tile
  ASSERT_EQ((*new_tile)->value().value(), 2); // test for correctly updated value
}

TEST(TestRules, WinCondition) {
  size_t side = 5;
  size_t x = 0;
  size_t y = 0;
  pie::Rules rules(side, x, y);

  // sequence:
  std::vector<std::pair<size_t, size_t>> sequence{
    std::make_pair(0ul, 3ul),
    std::make_pair(2ul, 1ul),
    std::make_pair(4ul, 3ul),
    std::make_pair(1ul, 3ul),
    std::make_pair(1ul, 0ul),
    std::make_pair(4ul, 0ul),
    std::make_pair(2ul, 2ul),
    std::make_pair(0ul, 4ul),
    std::make_pair(3ul, 4ul),
    std::make_pair(3ul, 1ul),
    std::make_pair(0ul, 1ul),
    std::make_pair(2ul, 3ul),
    std::make_pair(2ul, 0ul),
    std::make_pair(0ul, 2ul),
    std::make_pair(2ul, 4ul),
    std::make_pair(4ul, 2ul),
    std::make_pair(1ul, 2ul),
    std::make_pair(3ul, 0ul),
    std::make_pair(3ul, 3ul),
    std::make_pair(1ul, 1ul),
    std::make_pair(4ul, 1ul),
    std::make_pair(4ul, 4ul),
    std::make_pair(1ul, 4ul),
    std::make_pair(3ul, 2ul),
  };

  for (const auto& c: sequence) {
    rules.MoveTo(c.first, c.second);
  }

  ASSERT_TRUE(rules.Finished());
}