#include <gtest/gtest.h>
#include <algorithm>
#include "../src/math/primes.hpp"

// ==================== isPrime ====================

TEST(IsPrimeTests, One) {
  EXPECT_FALSE(isPrime(1));
}

TEST(IsPrimeTests, SmallPrimes) {
  EXPECT_TRUE(isPrime(2));
  EXPECT_TRUE(isPrime(3));
  EXPECT_TRUE(isPrime(5));
  EXPECT_TRUE(isPrime(7));
  EXPECT_TRUE(isPrime(11));
  EXPECT_TRUE(isPrime(13));
}

TEST(IsPrimeTests, SmallComposites) {
  EXPECT_FALSE(isPrime(4));
  EXPECT_FALSE(isPrime(6));
  EXPECT_FALSE(isPrime(9));
  EXPECT_FALSE(isPrime(15));
  EXPECT_FALSE(isPrime(25));
}

TEST(IsPrimeTests, LargePrime) {
  // 1e9 + 7 is the classic ICPC modular prime
  EXPECT_TRUE(isPrime(1000000007LL));
}

TEST(IsPrimeTests, LargeComposite) {
  // 1e9 + 9 = 1000000009 is prime, but 1e9 + 6 is not
  EXPECT_FALSE(isPrime(1000000006LL));
}

TEST(IsPrimeTests, PerfectSquareComposite) {
  // 49 = 7*7, tests that sqrt boundary is handled
  EXPECT_FALSE(isPrime(49));
  EXPECT_FALSE(isPrime(121)); // 11*11
}

// ==================== sieve_eratosthenes ====================

TEST(SieveTests, SieveUpToTen) {
  auto sieve = sieve_eratosthenes(10);
  // sieve[i] == true means i is prime
  EXPECT_FALSE(sieve[0]);
  EXPECT_FALSE(sieve[1]);
  EXPECT_TRUE(sieve[2]);
  EXPECT_TRUE(sieve[3]);
  EXPECT_FALSE(sieve[4]);
  EXPECT_TRUE(sieve[5]);
  EXPECT_FALSE(sieve[6]);
  EXPECT_TRUE(sieve[7]);
  EXPECT_FALSE(sieve[8]);
  EXPECT_FALSE(sieve[9]);
}

TEST(SieveTests, PrimeCountUpTo100) {
  auto sieve = sieve_eratosthenes(100);
  int count = 0;
  for (int i = 2; i < 100; i++) {
    if (sieve[i]) count++;
  }
  // There are 25 primes below 100
  EXPECT_EQ(count, 25);
}

TEST(SieveTests, PrimeCountUpToOneMillion) {
  auto sieve = sieve_eratosthenes(1000000);
  int count = 0;
  for (int i = 2; i < 1000000; i++) {
    if (sieve[i]) count++;
  }
  // There are 78498 primes below 10^6
  EXPECT_EQ(count, 78498);
}

TEST(SieveTests, SieveSize) {
  auto sieve = sieve_eratosthenes(50);
  EXPECT_GE((int)sieve.size(), 50);
}

TEST(SieveTests, ConsistencyWithIsPrime) {
  auto sieve = sieve_eratosthenes(200);
  for (int i = 2; i < 200; i++) {
    EXPECT_EQ(sieve[i], isPrime(i))
      << "Mismatch at i=" << i;
  }
}

// ==================== getSmallesPrimeFactorArray (SPF) ====================

TEST(SPFTests, SPFOfPrimesIsItself) {
  auto spf = getSmallesPrimeFactorArray(20);
  EXPECT_EQ(spf[2], 2);
  EXPECT_EQ(spf[3], 3);
  EXPECT_EQ(spf[5], 5);
  EXPECT_EQ(spf[7], 7);
  EXPECT_EQ(spf[11], 11);
  EXPECT_EQ(spf[13], 13);
  EXPECT_EQ(spf[17], 17);
  EXPECT_EQ(spf[19], 19);
}

TEST(SPFTests, SPFOfComposites) {
  auto spf = getSmallesPrimeFactorArray(30);
  EXPECT_EQ(spf[4], 2);   // 4 = 2*2
  EXPECT_EQ(spf[6], 2);   // 6 = 2*3
  EXPECT_EQ(spf[9], 3);   // 9 = 3*3
  EXPECT_EQ(spf[15], 3);  // 15 = 3*5
  EXPECT_EQ(spf[21], 3);  // 21 = 3*7
  EXPECT_EQ(spf[25], 5);  // 25 = 5*5
}

TEST(SPFTests, SPFOfPowersOfTwo) {
  auto spf = getSmallesPrimeFactorArray(65);
  EXPECT_EQ(spf[2], 2);
  EXPECT_EQ(spf[4], 2);
  EXPECT_EQ(spf[8], 2);
  EXPECT_EQ(spf[16], 2);
  EXPECT_EQ(spf[32], 2);
  EXPECT_EQ(spf[64], 2);
}

// ==================== primeFactorization ====================

TEST(PrimeFactorizationTests, FactorizationOfPrime) {
  auto spf = getSmallesPrimeFactorArray(20);
  auto factors = primeFactorization(spf, 13);
  std::sort(factors.begin(), factors.end());
  std::vector<long long> expected = {13};
  EXPECT_EQ(factors, expected);
}

TEST(PrimeFactorizationTests, FactorizationOfPowerOfTwo) {
  auto spf = getSmallesPrimeFactorArray(20);
  auto factors = primeFactorization(spf, 8);
  std::sort(factors.begin(), factors.end());
  // 8 = 2*2*2
  std::vector<long long> expected = {2, 2, 2};
  EXPECT_EQ(factors, expected);
}

TEST(PrimeFactorizationTests, FactorizationOfComposite) {
  auto spf = getSmallesPrimeFactorArray(100);
  auto factors = primeFactorization(spf, 60);
  std::sort(factors.begin(), factors.end());
  // 60 = 2*2*3*5
  std::vector<long long> expected = {2, 2, 3, 5};
  EXPECT_EQ(factors, expected);
}

TEST(PrimeFactorizationTests, FactorizationOfSquare) {
  auto spf = getSmallesPrimeFactorArray(50);
  auto factors = primeFactorization(spf, 36);
  std::sort(factors.begin(), factors.end());
  // 36 = 2*2*3*3
  std::vector<long long> expected = {2, 2, 3, 3};
  EXPECT_EQ(factors, expected);
}

TEST(PrimeFactorizationTests, ProductMatchesOriginal) {
  auto spf = getSmallesPrimeFactorArray(200);
  // Verify that multiplying all prime factors gives back the original number
  for (long long n = 2; n < 200; n++) {
    auto factors = primeFactorization(spf, n);
    long long product = 1;
    for (auto f : factors) product *= f;
    EXPECT_EQ(product, n)
      << "Product of factors of " << n << " doesn't match";
  }
}

TEST(PrimeFactorizationTests, AllFactorsArePrime) {
  auto spf = getSmallesPrimeFactorArray(200);
  for (long long n = 2; n < 200; n++) {
    auto factors = primeFactorization(spf, n);
    for (auto f : factors) {
      EXPECT_TRUE(isPrime(f))
        << f << " is not prime, found in factorization of " << n;
    }
  }
}
