#include <fstream>
#include <map>
#include <iostream>
#include <vector>
#include <string.h>
#include <queue>
#include <bitset>

using namespace std;

const int maxn = 505;

vector <pair<int,int> > g[maxn], gt[maxn];
int n, m, s, t, sink[maxn], source[maxn];
bitset <maxn> used;
map<pair<int, int>, bool>broken;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1391.in", "r", stdin);
	freopen("uri1391.out", "w", stdout);
	#endif



	while(true) {
		cin >> n >> m;
		if (n + m == 0)
			return 0;
		cin >> s >> t;
		for(int i = 0 ; i < m ; ++ i) {
			int x, y, z;
			cin >> x >> y >> z;
			g[x].push_back(make_pair(y, z));
			gt[y].push_back(make_pair(x, z));
		}
		memset(source, 0x3f3f3f3f, sizeof(source));
		priority_queue <pair<int, int>, vector <pair<int, int> > , greater<pair<int, int> > > q;
		q.push(make_pair(0, s));
		source[s] = 0;
		while (!q.empty()) {
			int cost = q.top().first;
			int node = q.top().second;
			q.pop();
			if(source[node] < cost)
				continue;
			for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it!=g[node].end(); ++ it)
				if(source[it->first] > cost + it->second) {
					source[it->first] = cost + it->second;
					q.push(make_pair(source[it->first], it->first));
				}
		}
		memset(sink, 0x3f3f3f3f, sizeof(sink));
		q.push(make_pair(0, t));
		sink[t] = 0;
		while(!q.empty()) {
			int cost = q.top().first;
			int node = q.top().second;
			q.pop();
			if(sink[node] < cost)
				continue;
			for(vector <pair<int, int> > :: iterator it = gt[node].begin() ; it!=gt[node].end() ; ++ it)
				if(sink[it->first] > cost + it->second) {
					sink[it->first] = cost + it->second;
					q.push(make_pair(sink[it->first], it->first));
				}
		}
		queue <int> Q;
		
		Q.push(s);
		used[s] = 1;
		while(!Q.empty()) {
			int node = Q.front();
			Q.pop();
			for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
				if(!used[it->first]){
					used[it->first] = 1;
					Q.push(it->first);
				}
				if(source[node] + it->second + sink[it->first] == source[t])
					broken[make_pair(node, it->first)] = 1;
			}
		}
	
		memset(source, 0x3f3f3f3f, sizeof(source));
		q.push(make_pair(0, s));
		source[s] = 0;
		while (!q.empty()) {
			int cost = q.top().first;
			int node = q.top().second;
			q.pop();
			if(cost > source[node])
				continue;
			for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it!=g[node].end() ; ++ it)
				if(!broken[make_pair(node, it->first)] && source[it->first] > cost + it->second) {
						source[it->first] = cost + it->second;
						q.push(make_pair(source[it->first], it->first));
				}
		}
		if(source[t] == 0x3f3f3f3f)
			cout << "-1\n";
		else
			cout << source[t] << "\n";

		for(int i = 0 ; i < n ; ++ i) {
			vector <pair<int, int> > ().swap(g[i]);
			vector <pair<int, int> > ().swap(gt[i]);
		}
		broken.clear();
		used.reset();
	}
}
