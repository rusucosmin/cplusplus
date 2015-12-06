#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

ofstream fout("tempest.out");

const int maxn = 100005;
const long long oo = (1LL << 60);

int t, n, m, z[3*maxn], s, d, k;
long long dist[maxn], sum;
vector <pair<int, int> > g[maxn];
vector <int> ans;
priority_queue<pair<long long, int> > q;

inline void dijkstra(int stnode) {
	for(int i = 1 ; i <= n ; ++ i)
		dist[i] = oo;
	dist[stnode] = 0;
	q.push(make_pair(0, stnode));
	while(!q.empty()) {
		long long cst = -q.top().first;
		int node = q.top().second;
		q.pop();
		if(dist[node] < cst)
			continue;
		for(auto it : g[node])
			if(dist[it.first] > cst + it.second) {
				dist[it.first] = cst + it.second;
				q.push(make_pair(-dist[it.first], it.first));
			}
	}
	ans.clear();
	for(int i = 1 ; i <= n ; ++ i)
		if(dist[i] <= sum)
			ans.push_back(i);
	printf("%d\n", int(ans.size()));
	for(auto it : ans)
		printf("%d ", it);
	printf("\n");
}

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getint(int &x) {
	while(!('0' <= buff[pos] && buff[pos] <= '9')) {
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	x = 0;
	while('0' <= buff[pos] && buff[pos] <= '9') {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
}

int main() {
	freopen("tempest.in", "r", stdin);
	freopen("tempest.out", "w", stdout);
	getint(t);
	while(t -- ){
		getint(n);
		getint(m);
		getint(s);
		getint(d);
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			getint(x);
			getint(y);
			getint(z[i]);
			g[x].push_back(make_pair(y, z[i]));
			g[y].push_back(make_pair(x, z[i]));
		}
		getint(k);
		sum = 0;
		for(int i = 1 ; i <= k ; ++ i) {
			int x;
			getint(x);
			sum += z[x];
		}
		dijkstra(d);
		for(int i = 1 ; i <= n ; ++ i)
			vector <pair<int, int> > ().swap(g[i]);
	}

}
