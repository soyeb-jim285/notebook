
/**
 * Author: CP algorithms
 * Description: Provides any solution of $ax+by=c$
 * Time: $O(\log(n))$
 * Status: Works
 */
#include "euclid.h"
bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
  g = euclid(abs(a), abs(b), x0, y0);
  if (c % g)
    return false;
  x0 *= c / g;
  y0 *= c / g;
  if (a < 0)
    x0 = -x0;
  if (b < 0)
    y0 = -y0;
  return true;
}
