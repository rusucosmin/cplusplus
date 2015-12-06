#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <queue>
#include <string.h>

using namespace std;

const int maxn = 50005;
const int oo = 0x3f3f3f3f;

int dist[maxn], n, m, inqs[maxn];
vector <pair<int, int> > g[maxn];
bitset <maxn> inq;

inline void bellmanford(ofstream &fout) {
	memset(dist, oo, sizeof(dist));
	queue <int> q;
	q.push(1);
	inq[1] = 1;
	dist[1] = 0;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		inq[node] = 0;
		for(auto it : g[node])
			if(dist[it.first] > dist[node] + it.second) {
				dist[it.first] = dist[node] + it.second;
				if(inq[it.first])
					continue;
				if(++ inqs[it.first] > n) {
					fout << "Ciclu negativ!\n";
					return;
				}
				inq[it.first] = 1;
				q.push(it.first);
			}
	}
	for(int i = 2 ; i <= n ; ++ i)
		fout << dist[i] << ' ';
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
	bellmanford(fout);
}
