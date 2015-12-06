#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxn = 500005;

int n, a[maxn], father[maxn];
long long down[maxn], totalSum, firstPlayer;
vector <int> g[maxn];

void dfs(int node) {
	down[node] = a[node];
	long long secondPlayer = 0;
	for(auto it : g[node]) {
		if(it == father[node])
			continue;
		father[it] = node;
		dfs(it);
		down[node] += down[it];
		secondPlayer = max(secondPlayer, down[it]);
	}
	secondPlayer = max(secondPlayer, totalSum - down[node]);
	firstPlayer = max(firstPlayer, totalSum - secondPlayer);
}

int main() {
	#ifdef HOME
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		totalSum += a[i];
	}
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1);
	cout << firstPlayer << '\n';
}
