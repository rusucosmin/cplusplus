#include <fstream>
#include <vector>
#include <iostream>
#include <bitset>

using namespace std;

const int maxn = 100005;

bitset <maxn> used, hasdad, ans;
int n, m, first[maxn], last[maxn], k, queries, letters, father[maxn];
vector <pair<int, int> > query[maxn];
vector <int> g[maxn];

struct update{
	int type, x, y;
	update(int a, int b, int c) {
		type = a;
		x = b;
		y = c;
	}
};

inline void dfs(int node) {
	first[node] = ++ k;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		dfs(*it);
	last[node] = ++ k;
}

inline int get(int x) {
	if(x != father[x])
		father[x] = get(father[x]);
	return father[x];
}

inline void unite(int x, int y) {
	father[get(x)] = get(y);
}

inline bool isparent(int x, int y) {
	if(first[x] <= first[y] && last[y] <= last[x])
		return 1;
	return 0;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("466e.in", "r", stdin);
	freopen("466e.out", "w", stdout);
	#endif
	vector <update> v;
	cin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int type, x, y;
		cin >> type;
		if(type == 1) {
			cin >> x >> y;	
			g[y].push_back(x);
			hasdad[x] = true;
			v.push_back(update(type, x, y));
		}
		else if(type == 2) {
			cin >> x; 
			v.push_back(update(type, x, ++ letters));
		}
		else {
			cin >> x >> y;	
			++ queries;
			query[y].push_back(make_pair(x, queries));
		}
		
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(!hasdad[i]) 
			dfs(i);
	
	for(int i = 1 ; i <= n ; ++ i)
		father[i] = i;
	
	for(vector <update> :: iterator it = v.begin() ; it != v.end() ; ++ it) {
		update u = *it;
		if(u.type == 1) {
			unite(u.x, u.y);	
		}
		if(u.type == 2) {
			int x = u.x;
			for(vector <pair<int, int> > :: iterator i = query[u.y].begin() ; i != query[u.y].end(); ++ i) {
				int y = i->first;
				int indecs = i->second;
				ans[indecs] = (get(x) == get(y) && isparent(y, x));	
			}
		}
	}
	for(int i = 1 ; i <= queries ; ++ i)
		if(ans[i])
			cout << "YES\n";
		else
			cout << "NO\n";
}
