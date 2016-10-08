#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define sorted_array tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define llong long long
#define long llong

int n_test;

void enter()
{
}

void solve()
{
}

void cleanup()
{
}

int main()
{
    ios::sync_with_stdio(false);
	if (ifstream("test.inp")) cin.rdbuf((new ifstream("test.inp"))->rdbuf());

	cin >> n_test;
	while (n_test--)
	{
		enter();
		solve();
		cleanup();
	}
}