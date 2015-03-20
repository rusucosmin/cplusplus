#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 100005;
const int maxlg = 20;
const int maxm = 6;

int n, m, k, a[maxm][maxn], rmq[maxm][maxlg][maxn], lg[maxn];

inline void buildrmq(int ind) {
	for(int l = 1 ; (1 << l) <= n ; ++ l) {
		int aux = (1 << (l - 1));
		for(int i = 1 ; i + (1 << l) - 1 <= n ; ++ i)
			rmq[ind][l][i] = max(rmq[ind][l - 1][i], rmq[ind][l - 1][i + aux]);
	}
}

inline int query(int ind, int i, int j) {
	int l = lg[j - i + 1];
	return max(rmq[ind][l][i], rmq[ind][l][j - (1 << l) + 1]);
}

inline bool check(int i, int j) {
	long long sum = 0;
	for(int aux = 1 ; aux <= m ; ++ aux)
		sum = sum + query(aux, i, j);
	return sum <= k;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("514d.in", "r", stdin);
	freopen("514d.out", "w", stdout);
	#endif
	
	cin >> n >> m >> k;
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= m ; ++ j)
			cin >> a[j][i], rmq[j][0][i] = a[j][i];
	}
	for(int i = 2 ; i <= n ; ++ i)
		lg[i] = lg[i >> 1] + 1;
	for(int j = 1 ; j <= m ; ++ j)
		buildrmq(j);
	int solution = 0, a = 0, b = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		int st = i, dr = n, ans = 0;
		while(st <= dr) {
			int mid = ((st + dr) >> 1);
			if(check(i, mid)) {
				ans = mid;
				st = mid + 1;
			}
			else
				dr = mid - 1;
		}
		if(ans == 0)
			continue;	
		if(solution < ans - i + 1) {
			solution = ans - i + 1;
			a = i;
			b = ans;
		}
	}
	if(solution == 0) {
		for(int i = 1 ; i <= m;  ++ i)
			cout << "0 ";
		return 0;
	}
	for(int i = 1 ; i <= m ; ++ i)
		cout << query(i, a, b) << ' ';
}
