#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <map>

using namespace std;

const int maxn = 102;

int n, m, k;
char s[maxn][maxn];
bitset <maxn * maxn> okay;
bitset <maxn> used[maxn * maxn];
vector <pair<int, bool> > g[maxn * maxn];

const int dx[] = {-1, 1, 0, 0};
const int dy[] = { 0, 0,-1, 1};

map<char, int> dir = {{'^', 0}, {'v', 1}, {'<', 2}, {'>', 3}};

inline int getnode(int x, int y) {
	return x * m + y;
}

inline int addedge(int a, int b, int c, int d, bool cost) {
	g[getnode(a, b)].push_back(make_pair(getnode(c, d), cost));
}

inline bool solve(int st) {
	queue <pair<int, int> > q;
	q.push(make_pair(st, 0));
	used[st][0] = 1;
	while(!q.empty()) {
		int node = q.front().first;
		int actk = q.front().second;

		q.pop();

		if(okay[node])
			return 1;

		for(vector <pair<int, bool> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
			actk += it->second;
			if(actk > k)
				continue;
			if(used[it->first][actk])
				continue;
			used[it->first][actk] = 1;
			q.push(make_pair(it->first, actk));
		}
	}
	return 0;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1525.in", "r", stdin);
	freopen("uri1525.out", "w", stdout);
	#endif
	while(cin >> n >> m >> k) {
		if((n + m + k) == 0)
			return 0;
		pair<int, int> start;
		for(int i = 0 ; i < n ; ++ i) {
			cin >> s[i];
			for(int j = 0 ; j < m ; ++ j) {
				if(i == 0 || i == n - 1 || j == 0 || j == m - 1)
					okay[getnode(i, j)] = 1;
				if(s[i][j] == 'x') {
					start = make_pair(i, j);
					continue;
				}
				int d = dir[s[i][j]];				
				int newx = i + dx[d];
				int newy = j + dy[d];
				if(newx >= 0 && newx < n && newy >= 0 && newy < m)
					addedge(newx, newy, i, j, 0);
				d ^= 1;
				newx = i + dx[d];
				newy = j + dy[d];
				if(newx >= 0 && newx < n && newy >= 0 && newy < m)
					addedge(newx, newy, i, j, 1);
			}
		}

		if(solve(getnode(start.first, start.second)))
			cout << "Sim\n";
		else
			cout << "Nao\n";

		okay.reset();
		for(int i = 0 ; i < n * m ; ++ i) {
			vector <pair<int, bool> > ().swap(g[i]);
			used[i].reset();
		}
	}
}
