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
inline int ccw(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}