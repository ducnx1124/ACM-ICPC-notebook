#include <bits/stdc++.h>
using namespace std;
#define llong long long
#define long llong

const int n_max = 100010;

int n;

struct point { double x, y; } A[n_max];

auto cmp_x = [](point a, point b) { return a.x < b.x; };
auto cmp_y = [](point a, point b) { return a.y < b.y; };

struct kdtree
{
	point P[n_max];

	void build(int l, int r, bool div_x)
	{
		if (l > r) return;

		int mid = l + (r - l) / 2;
		nth_element(A + l, A + mid, A + r + 1, div_x ? cmp_x : cmp_y);
		P[mid] = A[mid];

		build(l, mid - 1, !div_x);
		build(mid + 1, r, !div_x);
	}

	double get_nearest_square_dist(point p, int l = 1, int r = n, bool div_x = true)
	{
		if (l > r) return LLONG_MAX;

		int mid = l + (r - l) / 2;
		double dx = p.x - P[mid].x;
		double dy = p.y - P[mid].y;
		double dp = dx * dx + dy * dy;
		if (dp == 0) dp = LLONG_MAX;

		double d = div_x ? dx : dy;
		double d2 = d * d;

		if (d <= 0)
		{
			dp = min(dp, get_nearest_square_dist(p, l, mid - 1, !div_x));
			if (d2 < dp) dp = min(dp, get_nearest_square_dist(p, mid + 1, r, !div_x));
		} else
		{
			dp = min(dp, get_nearest_square_dist(p, mid + 1, r, !div_x));
			if (d2 < dp) dp = min(dp, get_nearest_square_dist(p, l, mid - 1, !div_x));
		}

		return dp;
	}
} T;

void enter()
{
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> A[i].x >> A[i].y;
}

void solve()
{
	T.build(1, n, true);

	double best = INFINITY;
	for (int i = 1; i <= n; ++i)
		best = min(best, T.get_nearest_square_dist(A[i]));

	cout << setprecision(3) << fixed << sqrt(best);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
	if (ifstream("test.inp")) cin.rdbuf((new ifstream("test.inp"))->rdbuf());

	enter();
	solve();
}