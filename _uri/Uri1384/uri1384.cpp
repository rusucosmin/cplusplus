#include <iostream>
#include <fstream>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const int maxn = 1005;
typedef pair<int, int> point;

const int cal[][5] = {
	{7, 6, 5, 6, 7},
	{6, 3, 2, 3, 6},
	{5, 2, 0, 2, 5},
	{6, 3, 2, 3, 6},
	{7, 6, 5, 6 ,7}
};

int n, m, w, dp[maxn][maxn];
pair<int, int> frog, girl;
bitset <maxn> used[maxn];
priority_queue < pair<int, point>, vector <pair<int,  point> >, greater<pair<int, point> > > q;

int main() {

	#ifndef ONLINE_JUDGE
	freopen("uri1384.in", "r", stdin);
	freopen("uri1384.out", "w", stdout);
	#endif

	while(true) {
		cin >> n >> m;
		if(n + m == 0)
			return 0;
		cin >> frog.first >> frog.second >> girl.first >> girl.second;
		cin >> w;
		for(int i = 1 ; i <= w ; ++ i) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			for(int x = a ; x <= c ; ++ x)
				for(int y = b ; y <= d ; ++ y)
					used[x][y] = 1;
		}
		memset(dp, 0x3f3f3f3f, sizeof(dp));
		dp[frog.first][frog.second] = 0;
		q.push(make_pair(0, frog));
		while(!q.empty()) {
			int cost = q.top().first;
			point p = q.top().second;
			q.pop();
			if(dp[p.first][p.second] < cost)	
				continue;
			for(int dx = -2 ; dx <= 2 ; ++ dx)
				for(int dy = -2 ; dy <= 2 ; ++ dy) {
					if(dx == 0 && dy == 0)
						continue;
					int newx = p.first + dx;
					int newy = p.second + dy;
					if(newx >= 1 && newx <= n && newy >= 1 && newy <= m && !used[newx][newy])
					if(dp[newx][newy] > cost + cal[dx + 2][dy + 2]) {
						dp[newx][newy] = cost + cal[dx + 2][dy + 2];
						q.push(make_pair(dp[newx][newy], make_pair(newx, newy)));
					}
				}
		}
	
		if(dp[girl.first][girl.second] == 0x3f3f3f3f)	
			cout << "impossible\n";
		else
			cout << dp[girl.first][girl.second] << '\n';

		for(int i = 1 ; i <= n ; ++ i)
			used[i].reset();
	}
	
}
