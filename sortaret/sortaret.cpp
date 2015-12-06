#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void dfs(int node, vector <bool> &used, vector<vector <int> > &gt, vector <int> &tsort) {
	used[node] = 1;
	for(auto it : gt[node])
		if(!used[it])
			dfs(it, used, gt, tsort);
	tsort.push_back(node);
}

vector <int> getTopologicalSort(int n, vector <vector <int> > &gt) {
	vector <bool> used(n, false);
	vector <int> tsort;
	for(int i = 0 ; i < n ; ++ i)
		if(!used[i])
			dfs(i, used, gt, tsort);
	return tsort;
}

int main() {
	ifstream fin("sortaret.in");
	ofstream fout("sortaret.out");
	int n, m;
	fin >> n >> m;
	vector <vector <int> > gt(n);
	while(m --) {
		int x, y;
		fin >> x >> y;
		-- x;
		-- y;
		gt[y].push_back(x);
	}
	vector <int> tsort = getTopologicalSort(n, gt);
	for(auto it : tsort)
		fout << it + 1 << ' ';
}
