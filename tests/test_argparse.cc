//
// Created by jesse on 11/18/18.
//
#include "gtest/gtest.h"

#include "lib/argparse/argparse.h"

TEST(ArgParse, GetArg) {
  int argc = 8;
  const char * const argv[] = {"progname", "-foo", "2", "-bar", "string", "-quz", "-quux", "3.14"};
  pie::ArgParser argparser{argc, (char**) argv};
  ASSERT_EQ(argparser.GetArg<int>("foo", 1), 2);
  ASSERT_EQ(argparser.GetArg<bool>("quz", false), true);
  ASSERT_EQ(argparser.GetArg<double>("quux", 1.23), 3.14);
}

TEST(ArgParse, ArgNotPresent) {
  int argc = 1;
  const char * const argv[] = {"progname"};
  pie::ArgParser argparser(argc, (char**) argv);
  ASSERT_EQ(argparser.GetArg<bool>("foo", false), false);
}
