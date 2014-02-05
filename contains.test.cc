#include <Base/contains.h>

#include <map>
#include <set>

#include <gtest/gtest.h>

TEST(Contains, Set) {
  std::set<int> x {23, 54, 24, 42};
  EXPECT_TRUE(Contains(x, 23));
  EXPECT_TRUE(Contains(x, 42));
  EXPECT_FALSE(Contains(x, 33));
}

