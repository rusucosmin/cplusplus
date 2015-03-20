#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <bitset>

using namespace std;

const int maxn = 100005;

int n, k;
unsigned long long s, sm, maxi, w[maxn], a[maxn];

inline unsigned long long check(unsigned long long q) {
	unsigned long long ans = 0ULL;
	for(int i = 1 ; i <= n ; ++ i)
		ans = ans + min(q, a[i]);	
	return ans;
}

inline unsigned long long binarysearch(unsigned long long li, unsigned long long ls) {
	unsigned long long mid, act;
	unsigned long long ans = 0;
	while(li <= ls) {
		mid = ((ls - li) / 2ULL) + li;
		act = check(mid);
		if(act >= sm - s) {
			ls = mid - 1;
			ans = mid;
		}
		else
			li = mid + 1;
	}
	return ans;
}

int main() {
	ifstream fin("vrejuri.in");
	ofstream fout("vrejuri.out");
	fin >> n >> k >> s;
	for(int i = 1 ; i <= n ; ++ i) {
		int h, p;
		fin >> h >> p;
		a[i] = 1ULL * h + 1ULL * k * p;
		sm = sm + a[i];
		maxi = max(maxi, a[i]);
	}
	unsigned long long q = binarysearch(0ULL, maxi);
	unsigned long long ans = 0ULL;
	unsigned long long cutsum = check(q);

	if(cutsum > sm - s) {
		-- q;
		unsigned long long actsum = check(q);
		unsigned long long toadd = sm - s - actsum;
		for(int i = 1 ; i <= n ; ++ i)
			w[i] = min(a[i], q);
		for(int i = 1 ; ; ++ i) {
			if(i == n + 1)
				i = 1;
			if(w[i] < a[i]) {
				++ w[i];
				-- toadd;
			}
			if(!toadd)
				break;
		}
	}
	else
		for(int i = 1 ; i <= n ; ++ i)
			w[i] = min(q, a[i]);
	for(int i = 1 ; i <= n ; ++ i)
		ans = ans + (k - w[i] % k) * (w[i] / k) * (w[i] / k) + (w[i] % k) * (w[i] / k + 1) * (w[i] / k + 1);
	fout << ans;
}
