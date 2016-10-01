#include <bits/stdc++.h>
#define N 1001
#define INF (int) 1e6 + 1
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
int n, m, s, t;
vector<int> g[N];
int c[N][N], d[N], f[N][N];
long long res;
bool findPath() {
    queue<int> q;
    rep(i, 1, n)
        d[i] = 0;
    d[s] = -1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == t)
            return true;
        for(auto v: g[u])
            if (!d[v] && c[u][v] > f[u][v]) {
                d[v] = u;
                q.push(v);
            }
    }
    return false;
}
void enlarge() {
    int u, v, delta = INF;
    v = t;
    while (v != s) {
        u = d[v];
        delta = min(delta, c[u][v] - f[u][v]);
        v = u;
    }
    v = t;
    while (v != s) {
        u = d[v];
        f[u][v] += delta;
        f[v][u] -= delta;
        v = u;
    }
    res += delta;
}
int main() {
    //freopen("input.txt", "r", stdin);
    scanf("%d%d%d%d", &n, &m, &s, &t);
    rep(i, 1, m) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back(v);
        g[v].push_back(u);
        c[u][v] = w;
    }
    while (findPath())
        enlarge();
    printf("%lld", res);
}
