#include <gtest/gtest.h>
#include "../src/math/divisors.hpp"

TEST(SimpleSieveTests, DivisorCountOfOne){
  auto result = simple_sieve(10);
  EXPECT_EQ(result[1], 1);
}

TEST(SimpleSieveTests, DivisorCountOfPrime){
  auto result = simple_sieve(10);
  // 7 is prime -> divisors are {1, 7} -> count = 2
  EXPECT_EQ(result[7], 2);
}

TEST(SimpleSieveTests, DivisorCountOfComposite){
  auto result = simple_sieve(13);
  // 12 -> divisors are {1,2,3,4,6,12} -> count = 6
  EXPECT_EQ(result[12], 6);
}

TEST(SimpleSieveTests, DivisorCountOfPerfectSquare){
  auto result = simple_sieve(17);
  // 16 -> divisors are {1,2,4,8,16} -> count = 5
  EXPECT_EQ(result[16], 5);
}

TEST(SimpleSieveTests, SmallPrimes){
  auto result = simple_sieve(20);
  // All primes should have exactly 2 divisors
  EXPECT_EQ(result[2], 2);
  EXPECT_EQ(result[3], 2);
  EXPECT_EQ(result[5], 2);
  EXPECT_EQ(result[11], 2);
  EXPECT_EQ(result[13], 2);
  EXPECT_EQ(result[17], 2);
  EXPECT_EQ(result[19], 2);
}

TEST(SimpleSieveTests, HighlyCompositeNumbers){
  auto result = simple_sieve(61);
  // 24 -> divisors {1,2,3,4,6,8,12,24} -> count = 8
  EXPECT_EQ(result[24], 8);
  // 36 -> divisors {1,2,3,4,6,9,12,18,36} -> count = 9
  EXPECT_EQ(result[36], 9);
  // 48 -> divisors {1,2,3,4,6,8,12,16,24,48} -> count = 10
  EXPECT_EQ(result[48], 10);
  // 60 -> divisors {1,2,3,4,5,6,10,12,15,20,30,60} -> count = 12
  EXPECT_EQ(result[60], 12);
}

TEST(SimpleSieveTests, PowersOfTwo){
  auto result = simple_sieve(65);
  // 2^k has k+1 divisors
  EXPECT_EQ(result[2], 2);   // 2^1
  EXPECT_EQ(result[4], 3);   // 2^2
  EXPECT_EQ(result[8], 4);   // 2^3
  EXPECT_EQ(result[32], 6);  // 2^5
  EXPECT_EQ(result[64], 7);  // 2^6
}

TEST(SimpleSieveTests, ResultSizeMatchesInput){
  auto result = simple_sieve(100);
  EXPECT_EQ(result.size(), 100);
}

TEST(SimpleSieveTests, ConsistencyWithGetDivisors){
  // The sieve result should match the number of divisors
  // returned by get_divisors for each number
  auto sieve = simple_sieve(50);
  for(int i = 1; i < 50; i++){
    auto divs = get_divisors(i);
    EXPECT_EQ(sieve[i], (long long)divs.size())
      << "Mismatch at i=" << i;
  }
}
