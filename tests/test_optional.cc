//
// Created by jesse on 10/22/18.
//
#include "gtest/gtest.h"
#include "optional.h"
#include "../util/macros.h"

TEST(TestOptional, Construct) {
  pie::Optional<int> q(0);
  pie::Optional<double> p(1.0);
  ASSERT_EQ(q.value(), 0);
  ASSERT_EQ(p.value(), 1.0);
}

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
  EXPECT_THROWS("Attempted value access on empty Optional", pie::OptionalAccessException, int s = r; (void)s);
}

TEST(TestOptional, Empty) {
  pie::Optional<int> o;
  ASSERT_FALSE(o.has_value());
  EXPECT_THROWS("Attempted value access on empty Optional", pie::OptionalAccessException, (void) o.value());
}

TEST(TestOptional, Bools) {
  pie::Optional<int> x = 1;
  pie::Optional<int> y = 1;
  pie::Optional<int> z = 0;
  ASSERT_EQ(x, y);
  ASSERT_NE(x, z);
  ASSERT_LE(z, x);
}

TEST(TestOptional, NonDefaultConstructible) {
  // non-default constructible test type
  struct Foo {
    explicit Foo(int x) : x(x) {}
    int x;
  };

  pie::Optional<Foo> opt_foo;
  Foo foo(1);
  opt_foo = foo;
  ASSERT_EQ(opt_foo.value().x, foo.x);
}

TEST(TestOptional, Deref) {
  pie::Optional<int> o = 1;
  ASSERT_EQ(*o, o.value());
}

TEST(TestOptional, Pointer) {
  int foo = 1;
  pie::Optional<int*> o_foo = &foo;
  ASSERT_EQ(&foo, *o_foo);
}

TEST(TestOptional, string) {
  std::string str = "foo";
  pie::Optional<std::string> o = str;
  ASSERT_EQ(o.value(), str);
}