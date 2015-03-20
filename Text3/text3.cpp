#include <fstream>
#include <string>
#include <vector>

using namespace std; 

vector <string> v;
vector <int> dp(26);
vector <int> last;
vector <int> ind(26, -1);
int sol, indecs;
string s;

ifstream fin("text3.in");
ofstream fout("text3.out");

inline void write(int node) {
	if(last[node] != -1)
		write(last[node]);
	fout << v[node] << '\n';
}

int main() {
	while (fin >> s)
		v.push_back(s);
	last.resize(v.size(), -1);
	for(int i = 0 ; i < v.size() ; ++ i) {
		int p = v[i][0] - 'a';
		int u = v[i][v[i].size() - 1] - 'a';
		last[i] = ind[p];
		if (dp[u] < dp[p] + 1) {
			dp[u] = dp[p] + 1;
			ind[u] = i;
		}
		if(dp[u] > sol) {
			sol = dp[u];
			indecs = i;
		}
				
	}

	fout << v.size() << '\n' << v.size() - sol << '\n';
	write(indecs);
}
