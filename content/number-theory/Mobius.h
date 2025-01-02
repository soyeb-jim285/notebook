/**
 * Author: Jim
 * Date: 2019-03-28
 * Description: The sieve of Eratosthenes computes the smallest prime factor for each number and the mobius function computes the mobius function for each number. 
 * Time: O(nloglogn) for sieve and O(n) for mobius
 * Status: Stress-tested
 */

ll const N = 1e7;
vector<ll> spf(N), mobius(N);
void sieve() {
  for (ll i = 2; i < N; i++) {
    if (spf[i] == 0) {
      for (ll j = i; j < N; j += i) {
        if (spf[j] == 0) {
          spf[j] = i;
        }
      }
    }
  }
}
void mobius() {
  for (ll i = 1; i < N; i++) {
    if (i == 1)
      mobius[i] = 1;
    else {
      if (spf[i / spf[i]] == spf[i])
        mobius[i] = 0;
      else
        mobius[i] = -1 * mobius[i / spf[i]];
    }
  }
}
