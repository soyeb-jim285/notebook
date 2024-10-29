/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds $nCr$ modulo a number that is not necessarily prime. Its
 * good when $m$ is small and not fixed. 
 * Time: $O(m\log m)$
 */

#include "../number-theory/CRT.h"
#include "../number-theory/ModPow.h"
int F[1000002] = {1}, p, e, pe;
ll lg(ll n, int p) {
  ll r = 0;
  while (n) n /= p, r += n;
  return r;
}
ll f(ll n) {
  if (!n) return 1;
  return modpow(F[pe], n / pe, pe) * (F[n % pe] * f(n / p) % pe) % pe;
}
ll ncr(ll n, ll r) {
  ll c;
  if ((c = lg(n, p) - lg(r, p) - lg(n - r, p)) >= e)
    return 0;
  for (int i = 1; i <= pe; i++)
    F[i] = F[i - 1] * (i % p == 0 ? 1 : i) % pe;
  return (f(n) * modpow(p, c, pe) % pe) * 
    modpow(f(r) * f(n - r), pe - (pe / p) - 1, pe) % pe;
}
ll ncr(ll n, ll r, ll m) {
  ll a0 = 0, m0 = 1;
  for (p = 2; m != 1; p++) {
    e = 0, pe = 1;
    while (m % p == 0)
      m /= p, e++, pe *= p;
    if (e) {
      a0 = crt(a0, m0, ncr(n, r), pe);
      m0 = m0 * pe;
    }
  }
  return a0;
}
