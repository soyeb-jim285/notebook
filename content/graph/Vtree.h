/**
 * Author: Farhan
* Description: Virtual tree
* Time: O(N \log N)
*/
vector<int> adj[N], new_adj[N];
int anc[N][LG], par[N], in[N], out[N], h[N], stk[N];
bool imp[N];
int ans = 0, _time = 0;
void dfs_pre(int ind, int p, int hi = 0) {
    in[ind] = _time++;
    anc[ind][0] = par[ind] = p;
    h[ind] = hi;
    for (auto i : adj[ind]) if (i != p) dfs_pre(i, ind, hi + 1);
    out[ind] = _time++;
}
bool is_anc(int u, int v) { return in[u] >= in[v] && out[u] <= out[v]; }
int get_lca(int u, int v) {
    if (is_anc(u, v)) return v;
    if (is_anc(v, u)) return u;
    for (int i = LG - 1; i >= 0; i--)
        if (!is_anc(u, anc[v][i])) v = anc[v][i];
    return anc[v][0];
}
void add_edge(int u, int v) {
    if (u != v) new_adj[u].push_back(v), new_adj[v].push_back(u);
}
void buildTree(vector<int> &nodes) {
    if (nodes.size() <= 1) return;
    sort(nodes.begin(), nodes.end(), [](int x, int y) { return in[x] < in[y]; });
    int root = get_lca(nodes[0], nodes.back()), ptr = 0;
    stk[ptr++] = root;
    for (int u : nodes) {
        int lca = get_lca(u, stk[ptr - 1]);
        while (ptr > 1 && h[stk[ptr - 2]] >= h[lca]) add_edge(stk[ptr - 2], stk[ptr - 1]), --ptr;
        if (stk[ptr - 1] != lca) add_edge(lca, stk[--ptr]), stk[ptr++] = lca, nodes.push_back(lca);
        stk[ptr++] = u;
    }
    for (int i = 0; i + 1 < ptr; ++i) add_edge(stk[i], stk[i + 1]);
}
int find_ans(int ind, int p) {
    int now = 0;
    if (imp[ind] && imp[p] && par[ind] == p && p != ind) return ans = -1e6, 0;
    for (auto i : new_adj[ind]) if (i != p) now += find_ans(i, ind);
    if (imp[ind]) return ans += now, 1;
    return (now > 1 ? ans++ : 0), now > 0;
}
void solve() {
    int n, q;
    cin >> n;
    for (int i = 0; i < n - 1; i++) { int x, y; cin >> x >> y; adj[x].push_back(y), adj[y].push_back(x); }
    dfs_pre(1, 1);
    for (int i = 1; i < LG; i++) for (int node = 1; node <= n; node++) anc[node][i] = anc[anc[node][i - 1]][i - 1];
    cin >> q;
    while (q--) {
        int k; cin >> k;
        vector<int> nodes(k);
        for (int &x : nodes) cin >> x, imp[x] = 1;
        buildTree(nodes);
        find_ans(nodes[0], nodes[0]);
        cout << (ans < 0 ? -1 : ans) << "\n";
        for (int i : nodes) new_adj[i].clear(), imp[i] = 0;
        ans = 0;
    }
}
