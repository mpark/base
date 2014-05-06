#include <base/thrower.h>

#include <gtest/gtest.h>

TEST(TThrower, Typical) {
  EXPECT_THROW(
      THROW(std::runtime_error) << "Some error message",
      std::runtime_error);
}

TEST(TThrower, LogicError) {
  EXPECT_THROW(
      THROW(std::logic_error) << "Damn, logic error...",
      std::logic_error);
}

