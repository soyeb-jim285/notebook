/**
 * Author: YouKnowWho
 * Description: Segment tree with lazy propagation.
 * Time: O(\log N) for upd/query, O(N \log N) for build.
 * Usage: segment_tree<ll> st; st.build(1, 1, n); st.upd(1, 1, n, l, r, v);
 * st.query(1, 1, n, l, r);
 */

const int N = 1e5 + 9;
int a[N];
struct segment_tree {
#define lc (n << 1)
#define rc ((n << 1) | 1)
  long long t[4 * N], lazy[4 * N];
  segment_tree() {
    memset(t, 0, sizeof t);
    memset(lazy, 0, sizeof lazy);
  }
  inline void push(int n, int b, int e) {
    if (lazy[n] == 0)
      return;
    t[n] = t[n] + lazy[n] * (e - b + 1);
    if (b != e) {
      lazy[lc] = lazy[lc] + lazy[n];
      lazy[rc] = lazy[rc] + lazy[n];
    }
    lazy[n] = 0;
  }
  inline long long combine(long long a, long long b) { return a + b; }
  inline void pull(int n) { t[n] = t[lc] + t[rc]; }
  void build(int n, int b, int e) {
    lazy[n] = 0;
    if (b == e) {
      t[n] = a[b];
      return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid);
    build(rc, mid + 1, e);
    pull(n);
  }
  void upd(int n, int b, int e, int i, int j, long long v) {
    push(n, b, e);
    if (j < b || e < i)
      return;
    if (i <= b && e <= j) {
      lazy[n] = v; // set lazy
      push(n, b, e);
      return;
    }
    int mid = (b + e) >> 1;
    upd(lc, b, mid, i, j, v);
    upd(rc, mid + 1, e, i, j, v);
    pull(n);
  }
  long long query(int n, int b, int e, int i, int j) {
    push(n, b, e);
    if (i > e || b > j)
      return 0; // return null
    if (i <= b && e <= j)
      return t[n];
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
};
