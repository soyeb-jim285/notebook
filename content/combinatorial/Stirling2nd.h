/**
 * Author: Fahim vai
 * Description: Stirling number of the second kind.
 * Time: O(k \log n)
 */
ll get_sn2(int n, int k) {
  ll sn2 = 0;
  for (int i = 0; i <= k; ++i) {
    ll now = nCr(k, i) * powmod(k - i, n, mod) % mod;
    if (i & 1) now = now * (mod - 1) % mod;
    sn2 = (sn2 + now) % mod;
  }
  sn2 = sn2 * ifact[k] % mod;
  return sn2;
}
