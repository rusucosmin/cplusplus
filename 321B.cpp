#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

const int maxn = 100005;

int n, d;
pair<int, int> p[maxn];
long long sum[maxn];

int main() {
	#ifdef HOME 
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif
	cin >> n >> d;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> p[i].first >> p[i].second;
	}
	sort(p + 1, p + n + 1);
	for(int i = 1 ; i <= n ; ++ i)
		sum[i] = sum[i - 1] + p[i].second;
	long long rasp = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		int st = i, dr = n;
		int ans = i;
		while(st <= dr) {
			int mid = (st + dr) / 2;
			if(p[mid].first - p[i].first < d) {
				st = mid + 1;
				ans = mid;
			}
			else
				dr = mid - 1;
		}
		rasp = max(rasp, sum[ans] - sum[i - 1]);
	}
	cout << rasp << '\n';
}
