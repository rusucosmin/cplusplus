#include <fstream>
#include <vector>
#include <bitset>
#include <stack>
#include <unordered_map>

using namespace std;

const int maxn = 5005;

vector <int> g[maxn], in[maxn / 10 + 5], out[maxn / 10 + 5];
int n, m, indeg[maxn], outdeg[maxn];
vector <pair<int, int> > edges;
vector <int> cycle;
pair<int, int> mymap[maxn];

inline void euler(int stnode) {
	stack <int> st;
	st.push(stnode);
	while(!st.empty()) {
		int node = st.top();
		if(!g[node].size()) {
			st.pop();
			cycle.push_back(node);
		}
		else {
			st.push(g[node].back());
			g[node].pop_back();
		}
	}
}

int main() {
	ifstream fin("tester.in");
	ofstream fout("tester.out");

	fin >> n >> m;
	for(int i = 0 ; i < m ; ++ i) {
		int x, y;
		fin >> x >> y;
		in[x].push_back(i);
		out[y].push_back(i);
		mymap[i] = make_pair(x, y);
		edges.push_back(make_pair(x, y));
	}
	for(int i = 1 ; i <= n ; ++ i) 
		for(vector <int> :: iterator x = in[i].begin() ; x != in[i].end() ; ++ x)
			for(vector <int> :: iterator y = out[i].begin() ; y != out[i].end() ; ++ y) {
				g[*y].push_back(*x);
				++ outdeg[*y];
				++ indeg[*x];
			}
	for(int i = 0 ; i < m ; ++ i) {
		int aux = max(outdeg[i] - indeg[i], indeg[i] - outdeg[i]);
		if(outdeg[i] > indeg[i])
			for(int j = 1 ; j <= aux ; ++ j) {
				g[m].push_back(i);	
				++ outdeg[m];
				++ indeg[i];
			}
		if(outdeg[i] < indeg[i])
			for(int j = 1 ; j <= aux ; ++ j) {
				g[i].push_back(m);
				++ outdeg[i];
				++ indeg[m];
			}
	}
	euler(m);
	for(int i = cycle.size() - 2 ; i >= 1 ; -- i)
		if(cycle[i] == m)
			fout << "R ";
		else {
			if(cycle[i + 1] == m)
				fout << mymap[cycle[i]].first << ' ';
			fout << mymap[cycle[i]].second << ' ';
		}
}
