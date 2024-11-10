/**
 * Author: Farhan
* Description: Virtual tree
* Time: O(N \log N)
*/
int anc[N][LG];
int par[N];
int _time = 0;
int in[N], out[N], h[N];

void dfs_pre(int ind, int p, int hi = 0)
{
    in[ind] = _time++;
    anc[ind][0] = p;
    par[ind] = p;
    h[ind] = hi;
    for (auto i : adj[ind])
        if (i != p)
            dfs_pre(i, ind, hi + 1);
    out[ind] = _time++;
}

bool is_anc(int ind, int anc)
{
    return in[ind] >= in[anc] and out[ind] <= out[anc];
}

int get_lca(int ind1, int ind2)
{
    if (is_anc(ind1, ind2))
        return ind2;
    if (is_anc(ind2, ind1))
        return ind1;

    for (int i = LG - 1; i >= 0; i--)
    {
        if (is_anc(ind1, anc[ind2][i]))
            continue;
        ind2 = anc[ind2][i];
    }
    return anc[ind2][0];
}

int stk[N];

void add_edge(int ind1, int ind2)
{
    if (ind1 == ind2)
        return;
    new_adj[ind1].push_back(ind2);
    new_adj[ind2].push_back(ind1);
}

void buildTree(vector<int> &nodes)
{
    if (nodes.size() <= 1)
        return;
    sort(nodes.begin(), nodes.end(), [](int x, int y)
         { return in[x] < in[y]; });
    int root = get_lca(nodes[0], nodes.back()), sz = nodes.size(), ptr = 0;
    ptr = 0, stk[ptr++] = root;
    for (int i = 0; i < sz; ++i)
    {
        int u = nodes[i], lca = get_lca(u, stk[ptr - 1]);
        if (lca == stk[ptr - 1])
        {
            stk[ptr++] = u;
        }
        else
        {
            while (ptr > 1 and h[stk[ptr - 2]] >= h[lca])
            {
                add_edge(stk[ptr - 2], stk[ptr - 1]), --ptr;
            }
            if (stk[ptr - 1] != lca)
            {
                add_edge(lca, stk[--ptr]);
                stk[ptr++] = lca, nodes.emplace_back(lca);
            }
            stk[ptr++] = u;
        }
    }
    if (find(nodes.begin(), nodes.end(), root) == nodes.end())
        nodes.emplace_back(root);
    for (int j = 0; j + 1 < ptr; ++j)
        add_edge(stk[j], stk[j + 1]);
}

bool imp[N];
int ans = 0;

int find_ans(int ind, int p)
{
    // cout << ind << " " << p << "\n";
    int now = 0;
    if (imp[ind] and imp[p] and par[ind] == p and p!=ind)
    {
        ans = -1e6;
        return 0;
    }
    for (auto i : new_adj[ind])
    {
        if(i!=p)now += find_ans(i, ind);
    }
    // cout << ind << " " << now << "\n";
    if (imp[ind])
    {
        ans += (now);
        return 1;
    }
    else
    {
        if (now > 1)
        {
            ans++;
            return 0;
        }
        else if (now == 1)
            return 1;
        else
            return 0;
    }
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs_pre(1, 1);
    for (int i = 1; i < LG; i++)
    {
        for (int node = 1; node <= n; node++)
        {
            anc[node][i] = anc[anc[node][i - 1]][i - 1];
        }
    }
    int q;
    cin >> q;
    while (q--)
    {
        int k;
        cin >> k;
        vector<int> nodes;
        for (int i = 0; i < k; i++)
        {
            int x;
            cin >> x;
            imp[x] = 1;
            nodes.push_back(x);
        }
        buildTree(nodes);
        sort(nodes.begin(), nodes.end(), [](int a, int b)
             { return in[a] < in[b]; });
        find_ans(nodes[0], nodes[0]);
        if (ans < 0)
            ans = -1;
        cout << ans << "\n";
        for (auto i : nodes)
        {
            new_adj[i].clear();
            imp[i] = 0;
        }
        ans = 0;
    }
}
