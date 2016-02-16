#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

const int maxn = 100005;
const int maxl = 1000005;
const int maxw = 1000000005;

int t, l, n, m, d;
int w[maxn];

inline bool check(long long tmp) {
	long long cnt = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		cnt += (tmp / w[i]);
	}
	return cnt >= l; 
}

inline long long binarySearch() {
	long long st = 0, dr = 1ll*maxl*maxw;
	long long ans = -1;
	while(st <= dr) {
		long long mid = ((dr - st) / 2 + st);
		if(check(mid)) {
			dr = mid - 1;
			ans = mid;
		}
		else
			st = mid + 1;
	}
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif

	cin >> t;
	for(int test = 1 ; test <= t ; ++ test) {
		cin >> l >> n >> m >> d;
		assert(1 <= n && n <= 100000);
		for(int i = 1 ; i <= n ; ++ i) {
			cin >> w[i];
		}
		long long tmp = binarySearch();
		vector <long long> rufe;
		for(int i = 1 ; i <= n ; ++ i) {
			for(long long j = 1 ; j <= tmp / w[i] && rufe.size() < l ; ++ j)
				rufe.push_back(1LL * j * w[i]);
		}
		sort(rufe.begin(), rufe.end());
		cout << "Case #" << test << ": ";
		if(n <= m)
			cout << rufe.back() + d << '\n';
		else {
			priority_queue <long long> q;
			for(int i = 1 ; i <= m ; ++ i) {
				q.push(0);
			}
			for(auto it : rufe) {
				long long finish = q.top();
				q.pop();
				finish = -finish;
				finish = max(finish, it) + d;
				q.push(-finish);
			}
			long long rasp = 0;
			while(!q.empty()) {
				rasp = -q.top();
				q.pop();
			}
			cout << rasp << '\n';
		}
	}
}
