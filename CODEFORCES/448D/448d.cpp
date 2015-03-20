#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100005;

int n, m;
long long k;

inline long long check(long long mid) {
	long long ret = 0;
	for(int i = 1 ; i <= n ; ++ i)
		ret += min(1LL*m, (mid - 1) / i);	
	return ret;
}

int main() {
	cin >> n >> m >> k;
	long long st = 1, dr = 1LL * n * m + 1;
	long long ret = -1;
	while(st <= dr) {
		long long mid = st + (dr - st) / 2;
		long long ans = check(mid);
		if(ans < k) {
			ret = mid;
			st = mid + 1;
		}
		else
			dr = mid - 1;
	}
	cout << ret << '\n';
}
