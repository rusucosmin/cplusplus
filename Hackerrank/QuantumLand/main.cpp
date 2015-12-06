#include <iostream>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <math.h>

using namespace std;

const int maxn = 100005;

int n, a[maxn], nr, father[maxn];
long double p[maxn], sum;
bitset <maxn> used;

void dfs(int node) {
		used[node] = 1;
		if(!used[a[node]]) {
			father[a[node]] = node;
			dfs(a[node]);
		}
		else {
			int dad = a[node];
			long double cycle_prod = p[node];
			while(node != dad && cycle_prod >= 0.00000000001) {
				node = father[node];
				cycle_prod *= p[node];
			}
			sum += cycle_prod;
		}
}

int main() {
	#ifdef HOME 
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i] >> p[i];
		p[i] = int(p[i]) / 100.0;
	}
	for(int i = 1 ; i <= n ; ++ i) {
		if(!used[i]) {
			dfs(i);
		}
	}
	cout << fixed << setprecision(2) << sum << '\n';
}
