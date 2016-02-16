#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 100005;

long long sum[maxn];
int p, n, t;

int bSearch(int i) {
	int st = 1;
	int dr = i;
	int ans = i + 1;
	while(st <= dr) {
		int mij = (st + dr) / 2;
		if(sum[i] - sum[mij - 1] <= p) {
			dr = mij - 1;
			ans = mij;
		}
		else
			st = mij + 1;
	}
	return ans;
}

int main() {
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);

	cin >> t;
	for(int test = 1 ; test <= t ; ++ test) {
		cout << "Case #" << test << ": ";
		cin >> n >> p;
		long long ans = 0;
		for(int i = 1 ; i <= n ; ++ i) {
			int x;
			cin >> x;
			sum[i] = sum[i - 1] + x;
			ans = ans + i - bSearch(i) + 1;
		}
		cout << ans << '\n';
	}
}
