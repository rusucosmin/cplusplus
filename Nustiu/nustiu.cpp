#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const int MAXN = 10005;

int T, N;
vector <int> g[MAXN];
bitset <MAXN> can;
vector <int> weight;

void dfs(int node, int father) {
	for(vector <int> :: iterator it = g[node].begin(), fin = g[node].end(); it != fin ; ++ it)
		if(*it != father) {
			dfs(*it, node); 
			can[node] = (can[node] & (weight[*it] <= N / 2));	
			weight[node] += weight[*it];
		}
	++ weight[node];
	if(node)
		can[node] = (can[node] & (N - weight[node] <=  N / 2));
}

int main() {
	ifstream fin ("nustiu.in");
	ofstream fout("nustiu.out");
	fin >> T;
	while (T --) {
		fin >> N;
		weight.resize(N);
		for(int i = 0 ; i < N ; ++ i) {
			vector <int>().swap(g[i]);
			can[i] = true;
			weight[i] = 0;
		}
		for(int i = 1 ; i != N ; ++ i) {
			int x, y;
			fin >> x >> y;
			--x; --y;
			g[x].push_back(y);
			g[y].push_back(x);
		}
		dfs(0, -1);
		bool is = false;
		for(int i = 0 ; i < N ; ++ i)
			if(can[i])
				fout << i + 1 << '\n', is = true;
		if(!is)
			fout << "NIMIC\n";
	}

}
