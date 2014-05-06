#include <base/split.h>

#include <gtest/gtest.h>

TEST(Split, Typical) {
  std::string line {"X\nX X "};
  auto tokens = Base::Split(line);
  for (const auto &token : tokens) {
    EXPECT_EQ(token, "X");
  }  // for
}

TEST(Split, Single) {
  std::string line {"X       \n"};
  auto tokens = Base::Split(line);
  for (const auto &token : tokens) {
    EXPECT_EQ(token, "X");
  }  // for
}

