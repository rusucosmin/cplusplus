#include <iostream>
#include <fstream>
#include <queue>
#include <bitset>
#include <string.h>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

ifstream fin("cartite.in");
ofstream fout("cartite.out");

const int maxn = 205;
const int oo = 0x3f3f3f3f;

int p, m, n, galerii, k, nodes;
pair<int, int> start;
int dp[maxn][maxn];
map <pair<int, int>, int > ind;
map <int, pair<int, int> > rev;
vector <int> g[maxn * maxn];

const int dx[] = {0, 1, 0,-1, 1,-1, 1, -1,-2, 0, 2, 0};
const int dy[] = {1, 0,-1, 0, 1, 1,-1, -1, 0,-2, 0, 2};

inline bool inside(int x, int y) {
	return x >= 1 && x <= m && y >= 1 && y <= n;
}

inline void bfs() {
	queue <pair<int, int> > q;
	q.push(start);
	if(dp[start.first][start.second] == -3) {
		fout << start.first << ' ' << start.second << ' ' << 0 << '\n';
		return ;
	}
	dp[start.first][start.second] = 0;
	while(!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;

		q.pop();

		for(int move = 0 ; move < 4 ; ++ move) {
			int newx = x + dx[move];
			int newy = y + dy[move];
			if(!inside(newx, newy))
				continue;
			if(dp[newx][newy] == -2)
				continue;
			if(dp[newx][newy] == -3) {
				fout << newx << ' ' << newy << ' ' << dp[x][y] + 1 << '\n';
				return ;
			}
			if(dp[newx][newy] == -1) {
				dp[newx][newy] = dp[x][y] + 1;
				q.push(make_pair(newx, newy));
			}
		}
	}
}

inline void euler() {
	stack <int> st;
	for(int i = 1 ; i <= n ; ++ i) {
		if(dp[rev[i].first][rev[i].second] != -2) {
			st.push(i);
			break;
		}
	}	
	vector <int> cycle;
	while(!st.empty()) {
		int node = st.top();
		if(g[node].size()) {
			int newnode = g[node].back();
			g[node].pop_back();
			g[newnode].erase(find(g[newnode].begin(), g[newnode].end(), node));
			st.push(newnode);
		}
		else {
			cycle.push_back(node);
			st.pop();
		}
	}
	reverse(cycle.begin(), cycle.end());
	for(int i = 0 ; i < cycle.size() ; ++ i)
		fout << rev[cycle[i]].first << ' ' << rev[cycle[i]].second << '\n';	
}

int main() {
	fin >> p;
	fin >> m >> n;
	fin >> start.first >> start.second;
	fin >> k;
	memset(dp, -1, sizeof(dp));
	for(int i = 1 ; i <= k ; ++ i) {
		int x, y, z, d = 0;
		fin >> x >> y >> z;
		dp[x][y] = -2;
		if(z == 1)
			d = 4;
		if(z == 2)
			d = 12;
		for(int move = 0 ; move < d ; ++ move) {
			int newx = x + dx[move];
			int newy = y + dy[move];
			if(inside(newx, newy))
				dp[newx][newy] = -2;
		}
	}
	/// -1 = liber
	/// -2 = vulpe
	/// -3 = gaura
	fin >> galerii;
	for(int i = 1 ; i <= galerii ; ++ i) {
		int x, y, a, b;
		fin >> x >> y >> a >> b;
		if(dp[x][y] == -1)
			dp[x][y] = -3;
		if(dp[a][b] == -1)
			dp[a][b] = -3;
		if(!ind[make_pair(x, y)]) {
			ind[make_pair(x, y)] =  ++ nodes;
			rev[nodes] = make_pair(x, y);
		}
		if(!ind[make_pair(a, b)]) {
			ind[make_pair(a, b)] = ++ nodes;
			rev[nodes] = make_pair(a, b);
		}
		g[ind[make_pair(x, y)]].push_back(ind[make_pair(a, b)]);
		g[ind[make_pair(a, b)]].push_back(ind[make_pair(x, y)]);
	}
	if(p == 1)
		bfs();
	else
		euler();
}
