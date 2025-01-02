/**
 * Author: Stjepan Glavina, chilli
 * Date: 2019-05-05
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * Description:
\\\begin{minipage}{75mm}
Returns a vector of the points of the convex hull in counter-clockwise order.
Points on the edge of the hull between two other points are not considered part of the hull.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Time: O(n \log n)
 * Status: stress-tested, tested with kattis:convexhull
*/
#pragma once

#include "Point.h"

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts, bool allow_collinear = false) {
  if (sz(pts) <= 1)
    return pts;
  sort(all(pts));
  pts.erase(unique(all(pts), [&](const P &a, const P &b) { return a == b; }),
            pts.end());
  vector<P> hull;
  auto condition = [&](const P &a, const P &b, const P &c) -> bool {
    ll cross = a.cross(b, c);
    if (allow_collinear)
      return cross < 0;
    else
      return cross <= 0;
  };
  for (const P &p : pts) {
    while (sz(hull) >= 2 &&
           condition(hull[sz(hull) - 2], hull[sz(hull) - 1], p))
      hull.pop_back();
    hull.push_back(p);
  }
  int lower_size = sz(hull) + 1;
  for (int i = sz(pts) - 1; i >= 0; --i) {
    const P &p = pts[i];
    while (sz(hull) >= lower_size &&
           condition(hull[sz(hull) - 2], hull[sz(hull) - 1], p))
      hull.pop_back();
    hull.push_back(p);
  }
  hull.pop_back();
  return hull;
}
