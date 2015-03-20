#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int n = 8, a[10][10], st[10][10];
bool used[10][10];

inline bool checkcube() {
	vector <long long> dist;
	unordered_map<long long, int> fr;
	for(int i = 1 ; i <= 8 ; ++ i) {
		for(int j = i + 1 ; j <= 8 ; ++ j) {
			long long act = 0;
			for(int k = 1 ; k <= 3 ; ++ k)
				act = act + 1LL * (a[i][st[i][k]] - a[j][st[j][k]]) * (a[i][st[i][k]] - a[j][st[j][k]]);
			dist.push_back(act);
			++ fr[act];
		}
	}
	sort(dist.begin(), dist.end());
	dist.resize(unique(dist.begin(), dist.end()) - dist.begin());
	if(dist.size() != 3)
		return false;
	if(!(fr[dist[0]] == 12 && fr[dist[1]] == 12 && fr[dist[2]] == 4))
		return false;
	if(dist[0]*2 == dist[1] && dist[2] == dist[0] * 3)
		return true;
	return false;
}

inline void back(int k, int p) {
	if(k == 9 && p == 1) {
		if(checkcube()) {
			cout << "YES\n";
			for(int i = 1 ; i <= 8 ; ++ i, cout << '\n')
				for(int j = 1 ; j <= 3 ; ++ j)
					cout << a[i][st[i][j]] << ' ';
			exit(0);
		}
		return ;	
	}
	for(int i = 1 ; i <= 3 ; ++ i) {
		if(used[k][i])
			continue;
		st[k][p] = i;
		used[k][i] = 1;
		if(p == 3)
			back(k + 1, 1);
		else
			back(k, p + 1);
		used[k][i] = 0;
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("465d.in", "r", stdin);
	freopen("465d.out", "w", stdout);
	#endif

	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= 3 ; ++ j)
			cin >> a[i][j];

	back(1, 1);
	cout << "NO\n";
}
