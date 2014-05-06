#include <base/optional.h>

#include <memory>

#include <gtest/gtest.h>

using namespace Base;

TEST(TOptional, Typical) {
  TOptional<int> optional;
  EXPECT_FALSE(optional);
  optional = 42;
  EXPECT_TRUE(!!optional);
  EXPECT_EQ(*optional, 42);
}

TEST(TOptional, MoveOnly) {
  TOptional<std::unique_ptr<int>> optional;
  EXPECT_FALSE(optional);
  optional = std::unique_ptr<int>(new int(42));
  EXPECT_TRUE(!!optional);
  EXPECT_EQ(**optional, 42);
}
