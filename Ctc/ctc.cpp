#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const int maxn = 100005;

vector <int> g[maxn], discovered, gt[maxn];
bitset <maxn> fol, used;
int n, m;
vector <vector <int> > ctc;

inline void dfs(int node) {
	if(used[node])
		return;
	cout << node << ' ';
	used[node] = 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!used[*it])
			dfs(*it);
	discovered.push_back(node);
}

inline void dfs2(int node, vector<int> &ctc) {
	used[node] = 1;
	ctc.push_back(node);
	for(vector <int> :: iterator it = gt[node].begin() ; it != gt[node].end() ; ++ it)
		if(!used[*it])
			dfs2(*it, ctc);
}

int main() {
	ifstream fin("ctc.in");
	ofstream fout("ctc.out");

	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		gt[y].push_back(x);
	}

	for(int i = 1 ; i <= n ; ++ i)
		if(!used[i])
			dfs(i);
	reverse(discovered.begin(), discovered.end());
	used.reset();
	for(int i = 0 ; i < discovered.size() ; ++ i) {
		int node = discovered[i];
		if(!used[node]) {
			vector <int> ans;
			dfs2(node, ans);
			ctc.push_back(ans);
		}
	}
	fout << ctc.size() << '\n';
	for(auto comp : ctc) {
		for(auto it : comp)
			fout << it << ' ';
		fout << '\n';
	}
}
