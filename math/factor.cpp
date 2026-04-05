#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> factor(ll k){
  vector<ll> factors;
  for(ll i = 1; i*i <= k; i++){
    if(k % i == 0){
      factors.push_back(i);
      if(k/i != i) factors.push_back(k/i);
    }
  }
  return factors;
}
void solve(){
  ll n;
  cin >> n;
  vector<ll> factors = factor(n);
  sort(factors.begin(), factors.end());
  for(auto x: factors) cout << x << " ";
}
int main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  ll t = 1;
  //cin >> t;
  while(t--) solve();
}
