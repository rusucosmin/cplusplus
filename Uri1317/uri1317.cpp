#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <bitset>

using namespace std;

const int maxn = 25;

struct message {
	int t1, t2;
	string a1, a2, a3;
	message(int _t1, int _t2, string _a1, string _a2, string _a3) {
		t1 = _t1;
		t2 = _t2;
		a1 = _a1;
		a2 = _a2;
		a3 = _a3;
	}
};

int n;
vector <message> m;
bitset <105> used[maxn];
map <pair<int, int>, int> howmany;
vector <int> g[maxn];

const int cost[][5] = {
	{7,6,5,6,7},
    {6,3,2,3,6},
	{5,2,0,2,5},
	{6,3,2,3,6},
	{7,6,5,6,7}
};

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1317.in", "r", stdin);
	freopen("uri1317.out", "w", stdout);
	#endif
	while(true) {
		cin >> n;
		if(n == 0)
			return 0;
		for(int i = 1 ; i <= n ; ++ i) {
			int x;
			while(cin >> x) {
				if(!x)
					break;
				g[i].push_back(x);
			}
		}
		queue <pair<int, int> > q;
		int stnode;
		int t1, t2;
		string a1, a2, a3;
		while(cin >> stnode) {
			if(!stnode)
				break;
			q.push(make_pair(stnode, m.size()));
			cin >> t1 >> t2 >> a1 >> a2 >> a3;
			m.push_back(message(t1, t2, a1, a2, a3));
		}
		while(!q.empty()) {
			int node = q.front().first;
			int mess = q.front().second;
			q.pop();
			if(used[node][mess])
				continue;
			used[node][mess] = 1;
			for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
				q.push(make_pair(*it, mess));
				++ howmany[make_pair(node, mess)];
			}
		}
		for(int i = 1 ; i <= n ; ++ i) {
			string name;
			cin >> name;
			cout << name << ": ";
			for(int j = 0 ; j < m.size() ; ++ j) {
				if(howmany[make_pair(i, j)] < m[j].t1)
					cout << m[j].a1 << ' ';
				else if(howmany[make_pair(i, j)] < m[j].t2)
					cout << m[j].a2 << ' ';
				else
					cout << m[j].a3 << ' ';
			}
			cout << '\n';
		}
		for(int i = 1 ; i <= n ; ++ i) {
			vector <int> ().swap(g[i]);
			used[i].reset();
		}
		vector <message> ().swap(m);
		howmany.clear();
	}
}
