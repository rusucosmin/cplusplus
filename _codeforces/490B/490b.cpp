#include <fstream>
#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

const int maxvalue = 1000005;
const int maxn = 200005;

int n, a[maxn], b[maxn], nxt[maxvalue];
bitset <maxvalue> used;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("490b.in", "r", stdin);
	freopen("490b.out", "w", stdout);
	#endif

	cin >> n;

	int second = 0;

	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i] >> b[i];
		used[b[i]] = 1;
		nxt[a[i]] = b[i];
		if(a[i] == 0)
			second = b[i];
	}

	vector <int> ans;

	for(int i = 1 ; i <= n && !ans.size() ; ++ i)
		if(!used[a[i]])
			ans.push_back(a[i]);

	ans.push_back(second);

	for(int i = 2 ; i < n ; ++ i)
		ans.push_back(nxt[ans[i - 2]]);

	for(auto it : ans)
		cout << it << ' ';

	


	
}
