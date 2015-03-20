#include <fstream>
#include <iostream>

using namespace std;

long long n;
long long ans;
int h;

inline bool isancestor(long long root, long long leaf, int height) {
	return root + 1 <= leaf && leaf <= root + (1LL << height);
}

inline void dfs(long long node, bool whichson, int height) {
	if(height == 0)
		return ;
	if(whichson == 0) {
		if(isancestor(0, n, height - 1))  {
			++ ans;
			dfs(2*node, !whichson, height - 1);
		}
		else {
			n -= (1LL << (height - 1));
			ans  += (1LL << (height));
			dfs(2*node + 1, whichson, height - 1);
		}
	}
	else {
		if(isancestor((1LL << (height - 1)), n, height)) {
			++ ans;
			n -= (1LL << (height - 1));
			dfs(2*node + 1, !whichson, height - 1);
		}
		else {
			ans += ((1LL << height));
			dfs(2*node, whichson, height - 1);
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("507c.in", "r", stdin);
	freopen("507c.out", "w", stdout);
	#endif

	cin >> h >> n;


	dfs(1, 0, h);

	cout << ans << '\n';
}
