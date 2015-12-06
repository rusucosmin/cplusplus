#include <iostream>
#include <fstream>
#include <map>

using namespace std;

const int maxn = 100005;
const int maxk = 30;

map<long long, long long> mp[maxk][maxk];
long long s, ans, a[maxn],f[maxn];
int n, k;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("525e.in", "r", stdin);
	freopen("525e.out", "w", stdout);
	#endif
    cin >> n >> k >> s;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
    mp[0][0][0] = 1;
    f[0] = 1;
	for(int i = 1 ; i <= 19 ; ++ i)
		f[i] = 1LL * f[i - 1] * i;
    for(int i = 0 ; i < n ; ++ i){
        long long k1 = a[i + 1];
		for(int j = 0 ; j <= k ; ++ j)
            for(auto it : mp[i][j])  {
                long long heh = it.first;
                long long skok = it.second;
                if(heh + k1 <= s)
					mp[i+1][j][heh+k1] += skok;
                if(k1 <= 19 && f[k1] + heh <= s && j < k)
					mp[i+1][j+1][heh+f[k1]] += skok;
                mp[i+1][j][heh] += skok;
            }
    }
	for(int j = 0 ; j <= k ; ++ j)
		ans += mp[n][j][s];
	cout << ans << '\n';
}
