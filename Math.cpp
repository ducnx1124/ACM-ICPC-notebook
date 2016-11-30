#include "bits/stdc++.h"

const double PI = acos(-1);

struct point
{
	long x, y;
	point(long x, long y): x(x), y(y) {}
};

// = 0 -> parallel
// > 0 -> left
// < 0 -> right
inline long ccw(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long euclid_extended(int nr, int r, int nt, int t)
{
	if (nr == 0) return t;
	return euclid_extended(r - r / nr * nr, nr, t - r / nr * nt, nt);
}

long inverse_mod(int x, int module)
{
	return euclid_extended(x, module, 1, 0);
}