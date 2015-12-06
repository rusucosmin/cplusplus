#include <iostream>
#include <string.h>
#include <fstream>
#include <bitset>
#include <queue>

using namespace std;

const int maxn = 1000005;

int dist[maxn];
queue <int> q;

inline int Inv(int x) {
	int ret = 0;
	while(x > 0) {
		ret = ret * 10 + x % 10;
		x /= 10;
	}
	return ret;
}

inline void bfs() {
	dist[1] = 1;
	q.push(1);
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node + 1 < maxn && dist[node + 1] == 0) {
			dist[node + 1] = dist[node] + 1;
			q.push(node + 1);
		}
		int inv = Inv(node);
		if(inv < maxn)
		if(dist[inv] == 0) {
			dist[inv] = dist[node] + 1;
			q.push(inv);
		}
	}
}

int main() {
	freopen("codejam1ba.in", "r", stdin);
	freopen("codejam1ba.out","w", stdout);
	int t;

	cin >> t;
	bfs();
	for(int test = 1 ; test <= t ; ++ test) {
		int n;
		cin >> n;
		cout << "Case #" << test << ": " << dist[n] << '\n';
	}
}
