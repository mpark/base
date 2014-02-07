#include <Base/split.h>

#include <gtest/gtest.h>

TEST(Split, Typical) {
  std::string line {"X\nX X "};
  auto tokens = Base::Split(line);
  for (const auto &token : tokens) {
    EXPECT_EQ(token, "X");
  }  // for
}

