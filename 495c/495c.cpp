#include <fstream>
#include <vector>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <stack>

using namespace std;

const int maxn = 100005;

char s[maxn];
int ans[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("495c.in", "r", stdin);
	freopen("495c.out", "w", stdout); 
	#endif
	cin >> s + 1;	
	int n = strlen(s + 1);
	
	int sum1 = 0, sum2 = 0;
	stack <int> st;
	bool okay = true;
	vector <int> v;
	for(int i = 1 ; i <= n ; ++ i) {
		if(s[i] == '(')
			st.push(i);
		else
			if(st.size() > 0) {
				st.pop();
				if(s[i] == '#') {
					++ ans[i];
					v.push_back(i);
				}
			}
			else
				okay = false;
	}

	while(!st.empty() && okay) {
		int pos = st.top();
		st.pop();
		bool added = false;
		vector <int> :: iterator it = upper_bound(v.begin(), v.end(), pos);
		if(it != v.end()) {
			added = true;
			++ ans[*it];
		}
		if(!added)
			okay = false;
	}

	if(!okay)
		cout << "-1\n";
	else
		for(int i = 1 ; i <= n ; ++ i)
			if(s[i] == '#')
				cout << ans[i] << '\n';
}
