#include <bits/stdc++.h>
using namespace std;
#define llong long long
#define long llong
#define ii pair<int,int>

const int n_max = 10010;

struct edge { int x, y, c; } E[n_max];

list<ii> G[n_max];
int M[n_max], H[n_max], I[n_max], IE[n_max], W[n_max], top_node[n_max], heavy_child[n_max], T[n_max * 4], P[n_max][16];
int n, m, n_test;

inline bool is_heavy (int x) { return M[x] * 2 > M[P[x][0]]; }

void dfs (int x,int h)
{   
    H[x] = h; M[x] = 1;

    for (list<ii>::iterator i = G[x].begin(); i != G[x].end(); ++i)
    if (i->first != P[x][0])
    {
        P[i->first][0] = x;
        W[i->first] = i->second;
        dfs(i->first, h + 1);
        M[x] += M[i->first];
    }
}

void load_path(int x)
{
    while (M[x] * 2 > M[P[x][0]]) I[x] = ++m, x = P[x][0];

    int p = x;
    while ((x = heavy_child[x]) > 0) IE[x] = m, top_node[x] = p;
}

void upd_edge (int u,int v,int x = 1,int l = 1,int r = m)
{
    if (l == r) { T[x] = v; return; }

    int k = x * 2, mid = (l + r) / 2;
    if (u <= mid)
        upd_edge(u, v, k, l, mid);
    else
        upd_edge(u, v, k + 1, mid + 1, r);

    T[x] = max(T[k], T[k + 1]);
}

int get_max (int u,int v,int x = 1,int l = 1,int r = m)
{
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return T[x];

    int k = x * 2, mid = (l + r) / 2;
    return max(get_max(u, v, k, l, mid),
               get_max(u, v, k + 1, mid + 1, r));
}

int lca (int x,int y)
{
    if (H[x] < H[y]) swap(x, y);

    for (int i = 15; i >= 0; --i)
    if (H[P[x][i]] >= H[y]) x = P[x][i];

    if (x == y) return x;

    for (int i = 15; i >= 0; --i)
    if (P[x][i] != P[y][i]) x = P[x][i], y = P[y][i];

    return P[x][0];
}

int get_max_edge (int x,int p) // p is x's ancestor
{
    int s = 0;

    while (x != p)
        if (is_heavy(x))
            if (H[top_node[x]] >= H[p]) // p is not in heavy path
            {
                s = max(s, get_max(I[x], IE[x]));
                x = top_node[x];
            } else // p is in heavy path
            {
                s = max(s, get_max(I[x], I[p] - 1));
                x = p;
            }
        else // advance normally
        {
            s = max(s, W[x]);
            x = P[x][0];
        }

    return s;
}

namespace query
{
    void change (int u,int v)
    {
        int x = (H[E[u].x] > H[E[u].y] ? E[u].x : E[u].y);

        W[x] = v;
        if (is_heavy(x)) upd_edge(I[x], v);
    }

    void query (int x,int y)
    {
        int p = lca(x, y);
        cout << max(get_max_edge(x, p), get_max_edge(y, p)) << "\n";
    }
}

void enter ()
{
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        cin >> E[i].x >> E[i].y >> E[i].c;
        G[E[i].x].push_back(ii (E[i].y, E[i].c));
        G[E[i].y].push_back(ii (E[i].x, E[i].c));
    }
}

void init ()
{
    dfs(1, 1);
    for (int j = 1; j < 16; ++j)
    for (int i = 1; i <= n; ++i)
        P[i][j] = P[P[i][j - 1]][j - 1];

    M[0] = 3 * n;
    for (int x = 1; x <= n; ++x)
    if (is_heavy(x)) heavy_child[P[x][0]] = x;

    for (int x = 1; x <= n; ++x)
    if (is_heavy(x) && heavy_child[x] == 0) load_path(x);

    for (int x = 1; x <= n; ++x)
    if (is_heavy(x)) upd_edge(I[x], W[x]);
}

void solve ()
{
    string s;
    int x, y;

    while (true)
    {
        cin >> s;
        if (s == "DONE") return;
        cin >> x >> y;

        if (s == "CHANGE") query::change(x, y);
        if (s == "QUERY") query::query(x, y);
    }
}

void clean_up ()
{
    fill_n(heavy_child + 1, n, 0);
    fill_n(top_node + 1, n, 0);
    fill_n(IE + 1, n, 0);
    fill_n(I + 1, n, 0);
    for (int i = 1; i <= n; ++i) G[i].clear();
    m = 0;
}

int main ()
{
    ios::sync_with_stdio(false); cin.tie(NULL);
    if (ifstream("test.inp")) cin.rdbuf((new ifstream("test.inp"))->rdbuf());

    cin >> n_test;
    while (n_test--)
    {
        enter();
        init();
        solve();
        clean_up();
    }
}