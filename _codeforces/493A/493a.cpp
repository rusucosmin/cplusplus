#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <bitset>

using namespace std;

const int maxn = 100;

string team[2];
map<pair<char, int>, int> fr;
int n;
bitset <maxn> done[2];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("493a.in", "r", stdin);
	freopen("493a.out", "w", stdout);
	#endif
	cin >> team[0] >> team[1] >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int minute, player;
		char type, color;
		cin >> minute >> type >> player >> color;
		if(type == 'h')
			type = 0;
		else
			type = 1;
		if(color == 'y')
			color = 1;
		else
			color = 2;
		fr[make_pair(type, player)] += color;
		if(fr[make_pair(type, player)] >= 2 && !done[type][player]) {
			cout << team[type] << ' ' << player << ' ' << minute << '\n';
			done[type][player] = 1;
		}
	}
	
	
}
