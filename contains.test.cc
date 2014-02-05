#include <Base/contains.h>

#include <map>
#include <set>

#include <gtest/gtest.h>

TEST(Contains, SetInt) {
  std::set<int> x {23, 54, 24, 42};
  EXPECT_TRUE(Base::Contains(x, 23));
  EXPECT_TRUE(Base::Contains(x, 42));
  EXPECT_FALSE(Base::Contains(x, 33));
}

TEST(Contains, SetStr) {
  const std::set<std::string> x {"X", "Y", "Z"};
  EXPECT_TRUE(Base::Contains(x, "X"));
  EXPECT_TRUE(Base::Contains(x, "Y"));
  EXPECT_FALSE(Base::Contains(x, "A"));
}

TEST(Contains, MapIntStr) {
  std::map<int, std::string> x {{23, "hello"}, {54, "world"}};
  auto iter = x.find(23);
  EXPECT_EQ(iter->second, "hello");
  Base::Contains(x, 23);
  EXPECT_TRUE(Base::Contains(x, 54));
  EXPECT_FALSE(Base::Contains(x, 33));
}

TEST(Contains, VectorInt) {
  std::vector<std::string> x {"hello", "world"};
  EXPECT_TRUE(Base::Contains(x, "hello"));
  EXPECT_TRUE(Base::Contains(x, "world"));
  EXPECT_FALSE(Base::Contains(x, "not here"));
}

TEST(Contains, Compatible) {
  const char *x[] = {"hello", "world"};
  EXPECT_TRUE(Base::Contains(x, std::string("hello")));
  EXPECT_TRUE(Base::Contains(x, std::string("world")));
  EXPECT_FALSE(Base::Contains(x, std::string("not here")));
}

