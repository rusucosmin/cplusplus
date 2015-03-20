#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int n, m;
vector <int> g[maxn];

inline bool eulerian() {
	for(int i = 1 ; i <= n ; ++ i)
		if(g[i].size() % 2 != 0 || !g[i].size())
			return false;
	return true;
}

inline void euler(int node, ofstream &fout) {
	vector <int> cycle;
	stack <int> st;
	st.push(node);
	while(!st.empty()) {
		int node = st.top();
		if(!g[node].empty()) {
			int newnode = g[node].back();
			g[node].pop_back();
			g[newnode].erase(find(g[newnode].begin(), g[newnode].end(), node));
			st.push(newnode);
		}
		else {
			st.pop();	
			if(!st.empty())
				cycle.push_back(node);
		}
	}
	for(vector <int> :: iterator it = cycle.begin() ; it != cycle.end() ; ++ it)
		fout << *it << ' ';
}

int main() {
	ifstream fin("ciclueuler.in");
	ofstream fout("ciclueuler.out");
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y; 
		g[x].push_back(y);
		g[y].push_back(x);
	}
	if(!eulerian()) {
		fout << "-1\n";
		return 0;
	}
	euler(1, fout);
}
