#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 16006;

int t, n, up[maxn], down[maxn];
vector <pair<int, int> > g[maxn];

inline void dfs(int node, int father) {
	for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(it->first == father)
			continue;
		dfs(it->first, node);
		down[node] = max(down[node], down[it->first] + it->second);
	}
}

inline void getmax(int &a, int &b, int c) {
	if(c > a) {
		b = a;
		a = c;
		return;
	}
	if(c > b)
		b = c;
}

inline void dfsup(int node, int father) {
	int a = up[node], b = 0;	
	for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(it->first == father)
			continue;
		getmax(a, b, down[it->first] + it->second); 
	}
	for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(it->first == father)
			continue;
		if(a == down[it->first] + it->second)
			up[it->first] = b;
		else
			up[it->first] = a;
		up[it->first] += it->second;
		dfsup(it->first, node);
	}
}

int main() {
	ifstream fin("razboi.in");
	ofstream fout("razboi.out");

	fin >> t;
	for(int test = 1 ; test <= t ; ++ test) {
		fout << "Testul nr #" << test << '\n';
		fin >> n;
		for(int i = 1 ; i < n ; ++ i) {
			int x, y, z;
			fin >> x >> y >> z;
			g[x].push_back(make_pair(y, z));
			g[y].push_back(make_pair(x, z));
		}
		dfs(1, 0);
		dfsup(1, 0);
		int ans = 0x3f3f3f3f;
		for(int i = 1 ; i <= n ; ++ i)
			if(ans > max(down[i], up[i]))
				ans = max(down[i], up[i]);
		for(int i = 1 ; i <= n ; ++ i)
			if(ans == max(down[i], up[i]))
				fout << i << '\n';
		for(int i = 1 ; i <= n ; ++ i) {
			down[i] = up[i] = 0;
			vector <pair<int, int> > ().swap(g[i]);
		}
	}
}
