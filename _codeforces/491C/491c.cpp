#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <string>
#include <string.h>
#include <unordered_map>

using namespace std;

const int maxn = 52;
const int maxnodes = 52 * 2 + 5;
const int oo = 0x3f3f3f3f;

vector <int> g[maxnodes];
unordered_map<int, unordered_map<int, int> > cap, cost;
unordered_map<int, char> decode;
unordered_map<char, int> aux;
int n, source, sink, k, dp[maxnodes], father[maxnodes];
string answers, s;
bitset <maxnodes> inq;
queue <int> q;

inline int geta(char x) {
	if('a' <= x && x <= 'z')
		return x - 'a';
	else
		return x - 'A' + 'z' - 'a' + 1;
}

inline int getb(char x) {
	return k + geta(x);
}

inline char getchara(int a) {
	if(0 <= a && a <= 25)
		return a + 'a';
	else
		return a + 'A' - 'z' + 'a' - 1;
}

inline char getcharb(int a) {
	return getchara(a - k);
}

inline bool bf() {
	memset(dp, oo, sizeof(dp));	
	dp[source] = 0;
	q.push(source);
	inq[source] = 1;
	while(!q.empty()) {
		int node = q.front();
		inq[node] = 0;
		q.pop();
		for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
			if(cap[node][*it] > 0 && dp[*it] > dp[node] + cost[node][*it]) {
				dp[*it] = dp[node] + cost[node][*it];
				father[*it] = node;
				if(inq[*it])
					continue;
				inq[*it] = 1;
				q.push(*it);
			}
		}
	}
	if(dp[sink] == oo)
		return 0;
	return 1;
}

inline int getmincostmaxflow() {
	int cost = 0;
	while(bf()) {
		int bottleneck = oo;
		for(int i = sink ; i != source ; i = father[i])
			bottleneck = min(bottleneck, cap[father[i]][i]);
		for(int i = sink ; i != source ; i = father[i]) {
			cap[father[i]][i] -= bottleneck;
			cap[i][father[i]] += bottleneck;
		}
		cost = cost + bottleneck * dp[sink];
	}
	return cost;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("491c.in", "r", stdin);
	freopen("491c.out", "w", stdout);
	#endif
	cin >> n >> k >> s >> answers;
	for(int i = 0 ; i < s.size() ; ++ i) {
		int x = geta(s[i]);
		int y = getb(answers[i]);
		decode[y] = answers[i];	
		if(!cap[x][y]) {
			g[x].push_back(y);
			g[y].push_back(x);
		}
		-- cost[x][y];
		++ cost[y][x];
		cap[x][y] = 1;
	}
	source = 2*k;
	sink = 2*k+1;
	for(int i = 0 ; i < k ; ++ i) {
		g[source].push_back(i);
		g[i].push_back(source);
		cap[source][i] = 1;
		cost[source][i] = 0;
	
		if(!decode[i])
			decode[i] = getchara(i + k);
	}
	for(int i = k ; i < 2 * k ; ++ i) {
		g[i].push_back(sink);
		g[sink].push_back(i);
		cap[i][sink] = 1;
		cost[i][sink] = 0;
	}
	cout << -getmincostmaxflow() << '\n'; 

	for(int i = 0 ; i < k ; ++ i) {
		int pair = i;
		for(vector <int> :: iterator it = g[i].begin() ; it != g[i].end() && pair == -1 ; ++ it)
			if(cap[i][*it] == 0 && i < *it && *it != source)
				pair = *it;
		cout << decode[pair];
	}
}
