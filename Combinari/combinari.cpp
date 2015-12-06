#include <fstream>

using namespace std;

const int maxn = 20;

ifstream fin("combinari.in");
ofstream fout("combinari.out");

int n, k, st[maxn];

void back(int p) {
	if(p == k + 1) {
		for(int i = 1 ; i <= k ; ++ i)
			fout << st[i] << ' ';
		fout << '\n';
		return ;
	}
	for(int i = st[p - 1] + 1 ; i <= n ; ++ i) {
		st[p] = i;
		back(p + 1);
	}
}

int main() {
	fin >> n >> k;
	back(1);
	
}
