#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxn = 100005;
const int inf = 0x3f3f3f3f;

int n;

void royfloyd(vector <vector <int> > &dist, vector <vector <int> > &minDist) {
	int n = dist.size();
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < n ; ++ j)
			minDist[i][j] = dist[i][j];
	for(int k = 0 ; k < n ; ++ k)
		for(int i = 0 ; i < n ; ++ i)
			for(int j = 0 ; j < n ; ++ j)
				minDist[i][j] = min(minDist[i][j], minDist[i][k] + minDist[k][j]);
}

int main() {
	ifstream fin("royfloyd.in");
	ofstream fout("royfloyd.out");
	
	fin >> n;
	vector <vector <int> > dist(n, vector <int> (n));
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < n ; ++ j) {
			fin >> dist[i][j];
			if(i != j && dist[i][j] == 0)
				dist[i][j] = inf;
		}
	vector <vector <int> > minDist(n, vector <int>(n, inf));
	royfloyd(dist, minDist);
	for(int i = 0 ; i < n ; ++ i, fout << '\n')
		for(int j = 0 ; j < n ; ++ j)
			if(minDist[i][j] == inf)
				fout << 0 << ' ';
			else
				fout << minDist[i][j] << ' ';
}
