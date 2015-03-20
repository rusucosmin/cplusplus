#include <fstream>
#include <iostream>
#include <queue>
#include <bitset>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 50005;
const int oo = 0x3f3f3f3f;

int n, m, dp[maxn], inqs[maxn];
bitset <maxn> inq;
vector <pair<int, int> > g[maxn];

inline bool bellmanford() {
	queue <int> q;
	q.push(1);
	memset(dp, oo, sizeof(dp));
	dp[1] = 0;
	inq[1] = 1;
	while(!q.empty()) {
		int node = q.front();
		inq[node] = false;
		q.pop();
		for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
			if(dp[it->first] > dp[node] + it->second) {
				dp[it->first] = dp[node] + it->second;
				if(inq[it->first])
					continue;
				inq[it->first] = 1;
				++ inqs[it->first];
				if(inqs[it->first] > n)
					return true;
				q.push(it->first);
			}
		}
	}
	return false;
}

int main() {
	ifstream fin("bellmanford.in");
	ofstream fout("bellmanford.out");
	
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		g[x].push_back(make_pair(y, z));
	}
	if(bellmanford()) {
		fout << "Ciclu negativ!\n";
		return 0;
	}
	else {
		for(int i = 2 ; i <= n ; ++ i)
			fout << dp[i] << ' ';
	}
}
