#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 100005;
const long long oo = 1000001000LL;

class aib{
public:
	long long a[maxn << 1];
	int n;
	aib(int _n) {
		n = _n;
		memset(a, 0, sizeof(a));
	}
	inline int lsb(int x) {
		return x & (-x);
	}
	inline void update(int pos, long long value) {
		for(int i = pos ; i <= n ; i += lsb(i)) {
			a[i] += value;	
		}
	}
	inline long long sum(int x) {
		long long _sum = 0;
		for(int i = x ; i > 0 ; i -= lsb(i))
			_sum += a[i];
		return _sum;
	}
} *aibs, *aibd;

struct keeper {
	int z, a, b;
	keeper(int _z, int _a, int _b) {
		z = _z;
		a = _a;
		b = _b;
	}
};

int n, m, k;
vector <int> g[maxn];
vector <keeper> v[maxn];
int anc[20][maxn], first[maxn], last[maxn], level[maxn];
long long dp[maxn], sum[maxn];

inline void dfs(int node, int father) {
	anc[0][node] = father;
	level[node] = level[father] + 1;
	first[node] = ++ k;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(*it == father)
			continue;
		dfs(*it, node);
	}
	last[node] = ++ k;
}

inline void buildancestors() {
	for(int l = 1 ; (1 << l) <= n ; ++ l)
		for(int i = 1 ; i <= n ; ++ i)
			anc[l][i] = anc[l - 1][anc[l - 1][i]];
}

inline int lca(int x, int y) {
	if(level[x] < level[y])
		swap(x, y);
	int log1 = 0, log2 = 0;
	for(log1 = 1 ; (1 << log1) < level[x] ; ++ log1);
	for(log2 = 1 ; (1 << log2) < level[y] ; ++ log2);
	
	for(int k = log1 ; k >= 0 ; -- k)
		if(level[x] - (1 << k) >= level[y])
			x = anc[k][x];
	if(x == y)
		return x;
	for(int k = log2 ; k >= 0 ; -- k)
		if(anc[k][x] != anc[k][y]) {
			x = anc[k][x];
			y = anc[k][y];
		}
	return anc[0][x];
}

inline long long getcost(int x, int y) {
	long long sumSum = aibs->sum(first[x]) + aibs->sum(first[y]);
	long long sumDp = aibd->sum(first[x]) + aibd->sum(first[y]);
	return sumSum - sumDp;
}

inline void dfs(int node) {
	dp[node] = oo;
	sum[node] = 0;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(*it == anc[0][node])
			continue;
		dfs(*it);
		sum[node] += dp[*it];
	}
	for(vector <keeper> :: iterator it = v[node].begin() ; it != v[node].end() ; ++ it) {
		dp[node] = min(dp[node], sum[node] + it->z + getcost(it->a, it->b));
	}
	aibd->update(first[node], dp[node]);
	aibd->update(last[node], -dp[node]);
	aibs->update(first[node], sum[node]);
	aibs->update(last[node], -sum[node]);
}

int main() {
	ifstream fin("paznici3.in");
	ofstream fout("paznici3.out");
	fin >> n >> m;
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1, 0);
	buildancestors();
	aibs = new aib(k);
	aibd = new aib(k);
	for(int i = 1 ; i <= m ; ++ i) {
		int z, a, b;
		fin >> z >> a >> b;
		v[lca(a, b)].push_back(keeper(z, a, b));
	}
	dfs(1);
	fout << dp[1] << '\n';
}
