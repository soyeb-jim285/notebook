/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Fast bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $btoa$ should be a vector full of
 * -1's of the same size as the right partition. Returns the size of
 * the matching. $btoa[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Usage: vi btoa(m, -1); hopcroftKarp(g, btoa);
 * Time: O(\sqrt{V}E)
 * Status: stress-tested by MinimumVertexCover, and tested on oldkattis.adkbipmatch and SPOJ:MATCHING
 */
#pragma once

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}
int hopcroftKarp(vector<vi>& g, vi& btoa) {
	int res = 0;
	vi A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(all(A), 0);
		fill(all(B), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		rep(a,0,sz(g))
			res += dfs(a, 0, g, btoa, A, B);
	}
}
=======
struct HopcroftKarp {
    int n, m;
    vector<int> l, r, lv, ptr;
    vector<vector<int>> adj;
    HopcroftKarp(int _n, int _m) : n(_n), m(_m), adj(n + m) {}
    void addEdge(int u, int v) { adj[u].emplace_back(v + n); }
    void bfs() {
        lv.assign(n, -1); queue<int> q;
        for (int i = 0; i < n; ++i) if (l[i] == -1) lv[i] = 0, q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) if (r[v] != -1 && lv[r[v]] == -1) {
                lv[r[v]] = lv[u] + 1; q.push(r[v]);
            }
        }
    }
    bool dfs(int u) {
        for (int &i = ptr[u]; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (r[v] == -1 || (lv[r[v]] == lv[u] + 1 && dfs(r[v]))) {
                l[u] = v, r[v] = u; return true;
            }
        }
        return false;
    }
    int maxMatching() {
        int match = 0;
        l.assign(n + m, -1), r.assign(n + m, -1);
        while (true) {
            ptr.assign(n, 0); bfs(); int cnt = 0;
            for (int i = 0; i < n; ++i) if (l[i] == -1 && dfs(i)) cnt++;
            if (cnt == 0) break; match += cnt;
        }
        return match;
    }
    void printMatching() {
        for (int i = 0; i < n; ++i) if (l[i] != -1) cout << l[i] - n + 1 << " ";
    }
};
>>>>>>> 7347265297ed97c7d322f02dd7c62d5d8303ec91
