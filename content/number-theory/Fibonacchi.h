/**
 * Author: Cp Algorithms: https://cp-algorithms.com/
 * Description: Fast doubling Fibonacci algorithm. Returns F(n) and F(n+1).
 * Time: O(\log n)
 */

pair<int, int> fib(int n) {
  if (n == 0)
    return {0, 1};
  auto p = fib(n >> 1);
  int c = p.first * (2 * p.second - p.first);
  int d = p.first * p.first + p.second * p.second;
  if (n & 1)
    return {d, c + d};
  else
    return {c, d};
}
