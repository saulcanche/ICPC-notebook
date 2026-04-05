#include <gtest/gtest.h>
#include <algorithm>
#include "../src/math/divisors.hpp"

TEST(MathTests, DivisorsOfNormalNumber){
  std::vector<long long> expected = {1, 2, 3, 4, 6, 12};
  auto result = get_divisors(12);
  std::sort(result.begin(), result.end());
  EXPECT_EQ(result, expected);
}

TEST(MathTests, DivisorsOfPrime){
  std::vector<long long> expected = {1, 7};
  auto result = get_divisors(7);
  std::sort(result.begin(), result.end());
  EXPECT_EQ(result, expected);
}

TEST(MathTests, DivisorsOfOne){
  std::vector<long long> expected = {1};
  EXPECT_EQ(expected, get_divisors(1));
}
