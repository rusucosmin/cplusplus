#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

const int maxn = 205;

bool used[maxn];
bool a[maxn][maxn];
bool ans;
int n, m, q;
vector <pair<int, int> > g[maxn];

inline void back(int node, int length, int st) {
	if(ans)
		return;
	if(!length) {
		if(node == st)
			ans = 1;
		return ;
	}
	for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(used[it->second])
			continue;
		used[it->second] = 1;
		back(it->first, length - 1, st);
		used[it->second] = 0;
	}
}

int main() {
	ifstream fin("ciclu2.in");
	ofstream fout("ciclu2.out");
	
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		a[x][y] = a[y][x] = 1;
		g[x].push_back(make_pair(y, i));
		g[y].push_back(make_pair(x, i));
	}
	fin >> q;
	for(int i = 1 ; i <= q ; ++ i) {
		int x, length;
		fin >> x >> length;
		ans = 0;
		back(x, length, x);
		fout << ans << '\n';
	}
}
