#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100005;

long long n, r, avg;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("492c.in", "r", stdin);
	freopen("492c.out", "w", stdout);
	#endif

	vector <pair<long long, long long > > v;

	
	cin >> n >> r >> avg;

	long long sum = 0;

	for(int i = 1 ; i <= n ; ++ i) {
		long long a, b;
		cin >> a >> b;
		v.push_back(make_pair(b, a));
		sum += a;
	}

	sort(v.begin(), v.end());

	long long ans = 0;

	for(int i = 0 ; i < n ; ++ i) {
		if(avg * n - sum >= 0) {
			long long nr = min(r - v[i].second, avg * n - sum);
			ans += nr * v[i].first;
			sum += nr;
		}
	}

	cout << ans << '\n';
}
