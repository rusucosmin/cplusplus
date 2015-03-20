#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

const int MAXN = 32005;
const int LOGN = 20;

ifstream fin("atac.in");
ofstream fout("atac.out");

int N, M, P, K, lvl[MAXN], Log[MAXN << 1], first[MAXN], father[LOGN][MAXN], dp[LOGN][MAXN], euler[MAXN << 1], level[MAXN << 1], rmq[LOGN][MAXN << 1];
vector <int> g[MAXN];

void buildDP() {
	for(int i = 1 ; (1 << i) <= N ; ++ i) {
		for(int j = 1 ; j <= N ; ++ j) {
			father[i][j] = father[i - 1][father[i - 1][j]];
			dp[i][j] = min(dp[i - 1][j], dp[i - 1][father[i - 1][j]]);
		}
	}
}

void dfs(int node, int actlevel) {
	euler[++ K] = node;
	level[K] = actlevel;
	first[node] = K;
	lvl[node] = actlevel;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		dfs(*it, actlevel + 1);
		euler[++ K] = node;
		level[K] = actlevel;
	}
} 

void buildRMQ() {
	for(int i = 2 ; i <= K ; ++ i)
		Log[i] = Log[i >> 1] + 1;
	for(int i = 1 ; i <= K ; ++ i) 
		rmq[0][i] = i;
	for(int i = 1 ; (1 << i) <= K ; ++ i) {
		int aux = (1 << (i - 1));
		for(int j = 1 ; j + (1 << i) - 1 <= K ; ++ j) {
			rmq[i][j] = rmq[i - 1][j];
			if(level[ rmq[i][j] ] > level[ rmq[i - 1][j + aux] ]) 
				rmq[i][j] = rmq[i - 1][j + aux];
		}
	}
}

int LCA(int x, int y) {
	x = first[x];
	y = first[y];
	if(x > y)
		swap(x, y);
	int l = Log[y - x + 1];
	int ret = rmq[l][x];
	if(level[ret] > level[rmq[l][y - (1 << l) + 1]])
		ret = rmq[l][y - (1 << l) + 1];
	return euler[ret];
}

int Query(int x, int y) {
	int many = lvl[x] - lvl[y];
	int ans = (1 << 30);
	for(int i = 0 ; (1 << i) <= many ; ++ i)
		if(many & (1 << i)) {
			if(dp[i][x] < ans)
				ans = dp[i][x];
			x = father[i][x];
		}
	return ans;
}

int main () {
	fin >> N >> M >> P;
	for(int i = 2 ; i <= N ; ++ i) {  
		fin >> father[0][i] >> dp[0][i];
		g[father[0][i]].push_back(i);
	}

	buildDP();
	dfs(1, 1);	
	buildRMQ();

	int x, y, a, b, c, d;
	fin >> x >> y >> a >> b >> c >> d;
	for(int i = 1 ; i <= M ; ++ i) {
		int lca = LCA(x, y);
		// cerr << x << ' ' << y << ' ' << lca << '\n';
		int z = min(Query(x, lca), Query(y, lca)) * (x != y);	
		if(i >= M - P + 1)
			fout << z << '\n';
		int xx = (x*a + y*b) % N + 1;
		int yy = (y*c + z*d) % N + 1;
		x = xx;
		y = yy;
	}
}

