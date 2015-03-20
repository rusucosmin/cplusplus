#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include <map>

using namespace std;

const int maxn = 100015;

int n, a[maxn];
map <int, int> mymap;

int main() {
	ifstream fin("patrate6.in");
	ofstream fout("patrate6.out");
	
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		fin >> a[i];
		++ mymap[a[i]];
	}
	int ans = -1;
	for(auto it : mymap) {
		int aux = it.second / 4;
		it.second %= 4;
		if(aux)
			mymap[it.first + 1] += aux;
		if(!it.second)
			mymap.erase(it.first);
	}
	for(auto it : mymap)
		if(it.second)
			ans = it.first;
	fout << ans + (mymap.size() != 1) << '\n';


}
