#include "divisors.hpp"
#include "../core.hpp"
vector<ll> get_divisors(ll k){
  vector<ll> divisors;
  for(ll i = 1; i*i <= k; i++){
    if(k % i == 0){
      divisors.push_back(i);
      if(k/i != i) divisors.push_back(k/i);
    }
  }
  return divisors;
}
vector<ll> simple_sieve(ll max_n){
  vector<ll> divisorsCount(max_n, 1);
  for(ll i = 2; i < max_n; i++){
    for(ll k = 1; k*i < max_n; k++) divisorsCount[i*k]++;
  }
  return divisorsCount;
}

