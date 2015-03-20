#include <fstream>
#include <bitset>
#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

const int maxn = 105;

int n, p, k, match[maxn];
vector <int> g[maxn];
bitset <maxn> used;

inline bool pairup(int node) {
	if(used[node])
		return false;
	used[node] = 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!match[*it] || pairup(match[*it])) {
			match[*it] = node;
			match[node] = *it;
			return 1;
		}
	return 0;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1489.in", "r", stdin);
	freopen("uri1489.out", "w", stdout);
	#endif
	cin >> k;
	for(int test = 1 ; test <= k ; ++ test) {
		memset(match, 0, sizeof(match));
		cin >> n;
		for(int i = 1 ; i <= n ; ++ i) {
			cin >> p;
			for(int j = 1 ; j <= p ; ++ j) {
				int x;
				cin >> x;
				g[i].push_back(x);
			}
		}
		
		int ans = 0;
		
		for(bool change = true ; change ; ) {
			change = false;
			used.reset();
			for(int i = 1 ; i <= n ; ++ i) {
				if(!match[i]) {
					if(pairup(i))
						++ ans;
				}
			}
		}
		cout << "Instance " << test << '\n';
		
		if(ans == n / 2)
			cout << "pair programming\n";
		else
			cout << "extreme programming\n";	
		cout << '\n';
	}
}
