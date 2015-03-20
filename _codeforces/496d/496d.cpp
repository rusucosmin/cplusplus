#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

const int maxn = 100005;

int sum[2][maxn], n;
vector <pair<int, int> > ans;

inline int binarySearch(int x, int li, int ls, int m) {
	int st = li, dr = ls;
	int ans = n + 1;
	while(st <= dr) {
		int mid = ((st + dr) >> 1);
		if(sum[x][mid] - sum[x][li - 1] >= m) {
			dr = mid - 1;
			if(sum[x][mid] - sum[x][li - 1] == m)
				ans = mid;
		}
		else
			st = mid + 1;
	}
	return ans;
}

inline void solve(int t) {
	int j = 1, scor[2], last;
	scor[0] = scor[1] = 0;
	while(j <= n) {
		int j0 = binarySearch(0, j, n, t);
		int j1 = binarySearch(1, j, n, t);
		int firstj = min(j0, j1);
		if(firstj == n + 1)
			return;	
		if(firstj == j0) {
			++ scor[0];
			last = 0;
		}
		if(firstj == j1) {
			++ scor[1];
			last = 1;
		}
		j = firstj + 1;
	}
	if(scor[0] > scor[1]) {
		if(last == 1)
			return;
		ans.push_back(make_pair(scor[0], t));
	}
	if(scor[1] > scor[0]) {
		if(last == 0)
			return;
		ans.push_back(make_pair(scor[1], t));
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("496d.in", "r", stdin);
	freopen("496d.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n; ++ i) {
		int x;
		cin >> x;
		sum[0][i] = sum[0][i - 1];
		sum[1][i] = sum[1][i - 1];
		-- x;
		++ sum[x][i];
	}
	for(int i = 1 ; i <= n ; ++ i)
		solve(i);
	sort(ans.begin(), ans.end());
	cout << ans.size() << "\n";
	for(auto it : ans)
		cout << it.first << ' ' << it.second << '\n';
}
