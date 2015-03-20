#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

const int maxn = 100005;

int a[maxn];
int k, n;
long long s[maxn];

inline long long sum(int x, int y, int z) {
	long long aux = s[y] - s[x - 1];
	long long diff = 1LL * (y - x + 1) * a[z];
	return abs(aux - diff);
	
}

inline bool check(int mid) {
	for(int i = 1 ; i + mid - 1 <= n ; ++ i) {
		int st = i;
		int dr = i + mid - 1;
		int m = (st + dr) / 2;
		int st1 = st;
		int dr1 = m;
		int st2 = m;
		int dr2 = dr;
		long long ret = sum(st1, dr1, dr1) + sum(st2, dr2, st2);
		if(ret <= k)
			return 1;
	}
	return 0;	
}

int main() {
	ifstream fin("noname2.in");
	ofstream fout("noname2.out");
	fin >> n >> k;
	for(int i = 1 ; i <= n ; ++ i) {
		fin >> a[i];
	}
	sort(a + 1, a + n + 1);
	for(int i = 1 ; i <= n ; ++ i)
		s[i] = s[i - 1] + a[i];
	
	int lo = 1, hi = n, ans = 1;
	while(lo <= hi) {
		int mid = ((lo - hi) >> 1) + hi;
		if(check(mid)) {
			lo = mid + 1;
			ans = mid;
		}
		else
			hi = mid - 1;
	}
	fout << ans << '\n';
}
