#include <bits/stdc++.h>
#define N 502
#define INF 1000001
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define per(i, b, a) for(int i = b; i >= a; i--)
#define bitcount(S) __builtin_popcount(S)
#define ll (long long)
#define db (double)
#define dbg(x) std::cout << x << std::endl
#define sz(x) x.size()
#define fi first
#define se second
using namespace std;
int n, m, k, p[N], res, s, t, d[N];
string st, a[N];
struct edge {
    int v, cap, f, cost, i;
    edge(int _v, int _cap, int _f, int _cost, int _i) {
        v = _v;cap = _cap;f = _f;cost = _cost; i = _i;
    }
};
vector<edge> g[N];
pair<int, int> pre[N];
bool in[N];

void addEdge(int u, int v, int cap, int cost) {
    edge a = edge(v, cap, 0, cost, g[v].size());
    edge b = edge(u, 0, 0, -cost, g[u].size());
    g[u].push_back(a);
    g[v].push_back(b);
}

void buildGraph() {
    rep(i, 0, n)
        addEdge(i, i + 1, k, 0);
    rep(i, 1, m)
        rep(j, 0, n - a[i].length())
            if (st.substr(j, a[i].length()) == a[i])
                addEdge(j, j + a[i].length(), 1, -p[i]);
    s = 0; t = n + 1;
}

bool fordBellman() {
    queue<int> q;
    rep(i, 1, n + 1) {
        d[i] = INF;
        in[i] = false;
    }
    d[s] = 0;
    q.push(s);
    in[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop(); in[u] = false;
        rep(i, 0, g[u].size() - 1) {
            edge e = g[u][i];
            if (e.cap > e.f && d[e.v] > d[u] + e.cost) {
                d[e.v] = d[u] + e.cost;
                pre[e.v] = make_pair(u, i);
                if (!in[e.v]) {
                    q.push(e.v);
                    in[e.v] = true;
                }
            }
        }
    }
    return (d[t] < INF);
}

void enlarge() {
    int v = t, delta = INF;
    int u, i, j;
    while (v != s) {
        u = pre[v].fi;
        i = pre[v].se;
        delta = min(delta, g[u][i].cap - g[u][i].f);
        v = u;
    }
    v = t;
    while (v != s) {
        u = pre[v].fi;
        i = pre[v].se;
        j = g[u][i].i;
        g[u][i].f += delta;
        g[v][j].f -= delta;
        v = u;
    }
    res -= d[t] * delta;
}

int main() {
    //freopen("input.txt", "r", stdin);
    cin >> n >> st >> m;
    rep(i, 1, m)
        cin >> a[i] >> p[i];
    cin >> k;
    buildGraph();
    while (fordBellman())
        enlarge();
    cout << res;
}
