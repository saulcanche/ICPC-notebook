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

