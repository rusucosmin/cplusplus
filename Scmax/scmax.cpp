#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

const int maxn = 100005;

int n, a[maxn], uniq, aib[maxn], dp[maxn], father[maxn];
map<int, int> mymap;

inline int lsb(int x) {
	return x & (-x);
}

inline void update(int x, int ind) {
	for(int i = x ; i <= uniq ; i += lsb(i)) {
		if(dp[aib[i]] < dp[ind])
			aib[i] = ind;
	}
}

inline int query(int x) {
	int ind = aib[x];
	for(int i = x ; i > 0 ; i -= lsb(i))
		if(dp[aib[i]] > dp[ind])
			ind = aib[i];
	return ind;
}

inline void write(int node, ofstream &fout) {
	if(father[node])
		write(father[node], fout);
	fout << a[node] << ' ';
}

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void get(int &x) {
	x = 0;
	while(!isdigit(buff[pos])) {
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	while(isdigit(buff[pos])) {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
}

int main() {
	ofstream fout("scmax.out");
	freopen("scmax.in", "r", stdin);

	get(n);
	bool edgecase = true;
	a[0] = 2000000000;
	for(int i = 1 ; i <= n ; ++ i) {
		get(a[i]);
		if(a[i] >= a[i - 1])
			edgecase = false;
		mymap[a[i]];
	}
	if(edgecase) {
		fout << "1\n" << a[1] << '\n';
		return 0;
	}
	for(map<int, int> :: iterator it = mymap.begin() ; it != mymap.end() ; ++ it)
		mymap[it->first] = ++ uniq;
	int ans = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		int best = query(mymap[a[i]] - 1);
		dp[i] = dp[best] + 1;
		update(mymap[a[i]], i);
		father[i] = best;
		ans = max(ans, dp[i]);
	}
	fout << ans << '\n';
	for(int i = 1 ; i <= n ; ++ i)
		if(dp[i] == ans) {
			write(i, fout);
			return 0;
		}
}
