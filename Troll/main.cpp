#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

ifstream fin("troll.in");
ofstream fout("troll.out");

vector < pair<pair<int, int>, int> > v;
int N, zmax, dp[2][100005]; 

int binarySearch(int li, int ls, int ind) {
	int st = li, dr = ls, ret = 0;
	while(st <= dr) {
		int mid = ((st + dr) >> 1);
		if(v[mid].first.first < v[ind].first.second) {
			ret = mid;
			st = mid + 1;
		}
		else 
			dr = mid - 1;
	}
	return ret;	
}

int main() {
	fin >> N;
	for(int i = 1 ; i <= N ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		v.push_back(make_pair(make_pair(y, x), z));
		zmax = max(zmax, z);
	}
	v.push_back(make_pair(make_pair(-1, -1), -1));
	sort(v.begin(), v.end());
	for(int i = 1 ; i <= N ; ++ i) {
		dp[0][i] = dp[0][i - 1];
		dp[1][i] = dp[1][i - 1];
		int pos = binarySearch(0, i - 1, i);
		if(v[i].second == zmax)
			dp[1][i] = max(dp[1][i], dp[0][pos] + 1);
		else
			dp[0][i] = max(dp[0][i], dp[0][pos] + 1);
		dp[1][i] = max(dp[1][i], dp[1][pos] + 1);
	}
	fout << zmax << ' ' << dp[1][N];
}
