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
