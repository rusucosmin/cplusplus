#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 100005;

int n, m, d, dp[maxn], father[maxn];
int aib[2][3*maxn];
long long a[maxn];
vector <long long> norm;

inline int lsb(int x) {
	return x & (-x);
}

inline void update(int wh, int pos, int ind) {
	for(int i = pos ; i <= m ; i += lsb(i))
		if(dp[ind] > dp[aib[wh][i]])
			aib[wh][i] = ind;
}

inline int query(int wh, int pos) {
	int ret = aib[wh][pos];
	for(int i = pos ; i > 0 ; i -= lsb(i))
		if(dp[ret] < dp[aib[wh][i]])
			ret = aib[wh][i];
	return ret;
}

inline void reconstr(int i) {
	if(i == 0)
		return;
	reconstr(father[i]);
	cout << i << ' ';
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("474e.in", "r", stdin);
	freopen("474e.out", "w", stdout);
	#endif
	cin >> n >> d;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		norm.push_back(a[i]);	
		norm.push_back(a[i] - d);
		norm.push_back(a[i] + d);
	}
	sort(norm.begin(), norm.end());
	norm.resize(unique(norm.begin(), norm.end()) - norm.begin());
	m = norm.size();

	int ans = 0; 

	for(int i = 1 ; i <= n ; ++ i) {
		int low = lower_bound(norm.begin(), norm.end(), a[i] - d) - norm.begin() + 1;	
		int up = lower_bound(norm.begin(), norm.end(), a[i] + d) - norm.begin() + 1; 
		int max1 = query(0, low);
		int max2 = query(1, m - up + 1);
		if(dp[max1] > dp[max2]) {
			dp[i] = dp[max1] + 1;	
			father[i] = max1;
		}
		else {
			dp[i] = dp[max2] + 1;	
			father[i] = max2;
		}
		ans = max(ans, dp[i]);
		update(0, lower_bound(norm.begin(), norm.end(), a[i]) - norm.begin() + 1, i);
		update(1, m - (lower_bound(norm.begin(), norm.end(), a[i]) - norm.begin()), i);
	}
	cout << ans << '\n';
	for(int i = 1 ; i <= n ; ++ i) {
		if(dp[i] == ans) {
			reconstr(i);	
			return 0;
		}
	}
}
