struct AC {
  int N = 0, P = 0, A = 10;
  vector<vector<int>> next{{A, 0}}, out{{}}, out_link{0}, link{0};

  int node() {
    next.emplace_back(A, 0), link.push_back(0), out_link.push_back(0), out.push_back({});
    return N++;
  }
  int add_pattern(const string &T) {
    int u = 0;
    for (char c : T) {
      if (!next[u][c - '0']) next[u][c - '0'] = node();
      u = next[u][c - '0'];
    }
    out[u].push_back(P);
    return P++;
  }
  void compute() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int c = 0; c < A; ++c) {
        int v = next[u][c];
        if (!v) next[u][c] = next[link[u]][c];
        else {
          link[v] = u ? next[link[u]][c] : 0;
          out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
          q.push(v);
        }
      }
    }
  }
  int advance(int u, char c) {
    while (u && !next[u][c - '0']) u = link[u];
    return next[u][c - '0'];
  }
  bool match(char c, int u) {
    u = advance(u, c);
    for (int v = u; v; v = out_link[v]) if (!out[v].empty()) return true;
    return false;
  }
};
