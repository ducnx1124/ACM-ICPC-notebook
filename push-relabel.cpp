#include <bits/stdc++.h>
using namespace std;
#define llong long long
#define long llong

const int n_max = 1010;

bool in_queue[n_max];
long E[n_max];
int G[n_max][n_max], F[n_max][n_max];
int H[n_max];
int n, xs, xt;

void push_flow(int x, int y)
{
	int flow = min((long)G[x][y] - F[x][y], E[x]);
	F[x][y] += flow;
	F[y][x] -= flow;
	E[x] -= flow;
	E[y] += flow;
}

void enter()
{
	int m, x, y;
	cin >> n >> m >> xs >> xt;

	while (m--)
	{
		cin >> x >> y;
		cin >> G[x][y];
	}
}

void solve()
{
	list<int> P;

	H[xs] = n;
	E[xs] = LLONG_MAX;
	for (int y = 1; y <= n; ++y)
	if (G[xs][y] > 0)
	{
		push_flow(xs, y);
		P.push_back(y);
		in_queue[y] = true;
	}

	while (!P.empty())
	{
		int x = P.front();
		int h_min = INT_MAX;

		for (int y = 1; y <= n; ++y)
		if (G[x][y] > F[x][y])
		{
			if (H[y] >= H[x]) h_min = min(h_min, H[y]);
			else
			{
				push_flow(x, y);
				if (!in_queue[y] && y != xs && y != xt) P.push_back(y), in_queue[y] = true;
			}
		}

		if (E[x] > 0) H[x] = h_min + 1;
		else
		{
			P.pop_front();
			in_queue[x] = false;
		}
	}

	cout << E[xt] << "\n";
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
	if (ifstream("test.inp")) cin.rdbuf((new ifstream("test.inp"))->rdbuf());

	enter();
	solve();
}