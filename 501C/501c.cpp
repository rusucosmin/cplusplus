#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int maxn = (1 << 16);

int deg[maxn], s[maxn], n;
queue <int> q;
vector <pair<int, int> > edges;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("501c.in", "r", stdin);
	freopen("501c.out", "w", stdout);
	#endif

	cin >> n;
	for(int i = 0 ; i < n ; ++ i) {
		cin >> deg[i] >> s[i];
		if(deg[i] == 1)
			q.push(i);	
	}

	while(!q.empty()) {
		int node = q.front();
		q.pop();
		
		if(deg[node] == 0)
			continue;

		edges.push_back(make_pair(node, s[node]));
		-- deg[s[node]];
		s[s[node]] ^= node;

		if(deg[s[node]] == 1)
			q.push(s[node]);
	}

	cout << edges.size() << '\n';
	for(vector <pair<int, int> > :: iterator it = edges.begin() ; it != edges.end() ; ++ it)
		cout << it->first << ' ' << it->second << '\n';
}
