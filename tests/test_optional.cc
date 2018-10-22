//
// Created by jesse on 10/22/18.
//
#include "gtest/gtest.h"
#include "optional.h"


TEST(TestOptional, Construct) {
  pie::Optional<int> o = 1;
  pie::Optional<double> p(1.0);
  ASSERT_EQ(o.value(), 1);
  ASSERT_EQ(p.value(), 1.0);
};

TEST(TestOptional, Assign) {
  pie::Optional<int> o;
  o = 1;
  ASSERT_EQ(o.value(), 1);
}

TEST(TestOptional, Convert) {
  pie::Optional<int> o = 1;
  int p = o;
  double q = o;
  ASSERT_EQ(p, o.value());
  ASSERT_EQ(static_cast<double>(o.value()), q);
  pie::Optional<int> r;
  ASSERT_ANY_THROW(int s = r);
}

TEST(TestOptional, Empty) {
  pie::Optional<int> o;
  ASSERT_FALSE(o.has_value());
  ASSERT_ANY_THROW(o.value());
  ASSERT_ANY_THROW(int x = o);
}

TEST(TestOptional, Bools) {
  pie::Optional<int> x = 1;
  pie::Optional<int> y = 1;
  pie::Optional<int> z = 0;
  ASSERT_EQ(x, y);
  ASSERT_NE(x, z);
  ASSERT_LE(z, x);
}
