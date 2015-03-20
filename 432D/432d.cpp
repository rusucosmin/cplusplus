#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100005;

char s[maxn];
int n, pi[maxn], cnt[maxn];

int main() {
	cin >> s + 1;
	n = strlen(s + 1);
	int k = 0;
	for(int i = 2 ; i <= n ; ++ i) {
		while(k > 0 && s[k + 1] != s[i])
			k = pi[k];
		if(s[k + 1] == s[i])
			++ k;
		pi[i] = k;
		++ cnt[pi[i]];
	}
	for(int i = n ; i >= 1 ; -- i)
		cnt[pi[i]] += cnt[i];
	k = n;
	vector <pair<int, int> > v;
	while(k) {
		v.push_back(make_pair(k, cnt[k] + 1));
		k = pi[k];	
	}
	sort(v.begin(), v.end());
	cout << v.size() << '\n';
	for(auto it : v)
		cout << it.first << ' ' << it.second << '\n';
}
