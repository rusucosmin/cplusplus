#include <iostream>
#include <vector>

using namespace std;

const int maxn = 3005;

bool g[maxn][maxn];
vector <int> adj[maxn];
int n, m;

int main() {
	cin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x][y] = 1;
		adj[x].push_back(y);
	}
	long long ans = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= n ; ++ j) {
			if(i == j)
				continue;
			int r = 0;
			for(vector <int> :: iterator it = adj[i].begin() ; it != adj[i].end() ; ++ it)
				if(*it != i && *it != j && g[*it][j])
					++ r;
			ans += (1LL * r * (r - 1)) / 2;
		}
	}
	cout << ans << '\n';
	
}
