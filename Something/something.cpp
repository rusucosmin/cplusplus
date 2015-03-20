#include <fstream>
#include <stdlib.h>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 100005;

ifstream fin("something.in");
ofstream fout("something.out");

int n, m, cx, cy, dad[maxn], color[maxn];
vector <int> g[maxn];
bitset <maxn> used;
bool found;

inline void doColor(int node, int col) {
	color[node] = col;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!color[*it])
			doColor(*it, col);
}

inline void solve() {
	int node = cx;
	for( node = cx ; node != dad[cy] ; node = dad[node])
		color[node] = 1;
	color[cx] = 2;
	color[cy] = 3;
	doColor(cx, 2);
	doColor(cy, 3);
	for(int i = 1 ; i <= n ; ++ i) {
		if(color[i] == 0)
			color[i] = 1;
		fout << color[i] << ' ';
	}
	exit(0);
}

inline void dfs(int node, int father) {
	used[node] = 1;	
	dad[node] = father;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(*it == father)
			continue;
		if(used[*it]) {
			cx = node;
			cy = *it;
			solve();
		}
		dfs(*it, node);
	}
}

int main() {
	fin >> n >> m;

	while (m --) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}

	dfs(1, 0);

	fout << "-1\n";

	

}
