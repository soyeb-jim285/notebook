/**
 * Author: Farhan
* Description: Virtual tree
* Time: O(N \log N)
*/
void buildTree (vector <int> &nodes) {
  if (nodes.size() <= 1) return;
  sort(nodes.begin(), nodes.end(), [] (int x, int y) {return in[x] < in[y];});
  int root = get_lca(nodes[0], nodes.back()), sz = nodes.size();
  ptr = 0, stk[ptr++] = root;
  for (int i = 0; i < sz; ++i) {
    int u = nodes[i], lca = get_lca(u, stk[ptr - 1]);
    if (lca == stk[ptr - 1]) {
      stk[ptr++] = u;
    } else {
      while (ptr > 1 and h[stk[ptr - 2]] >= h[lca]) {
        add_edge(stk[ptr - 2], stk[ptr - 1]), --ptr;
      }
      if (stk[ptr - 1] != lca) {
        add_edge(lca, stk[--ptr]);
        stk[ptr++] = lca, nodes.emplace_back(lca);
      }
      stk[ptr++] = u;
    }
  }
  if (find(nodes.begin(), nodes.end(), root) == nodes.end()) nodes.emplace_back(root);
  for (int j = 0; j + 1 < ptr; ++j) add_edge(stk[j], stk[j + 1]);
}
