#include <base/demangle.h>

#include <vector>

#include <gtest/gtest.h>

struct TBase {

  virtual ~TBase() {}

};

struct TDerived : TBase {};

TEST(Demangle, Typical) {
  EXPECT_EQ(Base::Demangle<int>(), std::string("int"));
  EXPECT_EQ(Base::Demangle<const int>(), std::string("int"));
  EXPECT_EQ(Base::Demangle<int &>(), std::string("int"));
  EXPECT_EQ(Base::Demangle<const int &&>(), std::string("int"));
  EXPECT_EQ(Base::Demangle<int []>(), std::string("int []"));
  EXPECT_EQ(Base::Demangle<int *>(), std::string("int*"));
  EXPECT_EQ(Base::Demangle<const int *>(), std::string("int const*"));
  EXPECT_EQ(Base::Demangle<int *>(), std::string("int*"));
  EXPECT_EQ(Base::Demangle<std::string>(), std::string("std::string"));
  EXPECT_EQ(Base::Demangle(typeid(std::string)), std::string("std::string"));
  EXPECT_EQ(Base::Demangle(typeid(TBase)), std::string("TBase"));
  EXPECT_EQ(Base::Demangle(typeid(TDerived)), std::string("TDerived"));
  TDerived derived;
  const TBase &base = derived;
  EXPECT_EQ(Base::Demangle(typeid(base)), std::string("TDerived"));
}
