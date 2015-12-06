#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

int main(){
	vector <int> elmaj;
	int t, n;
	ifstream fin("avarcolaci.in");
	ofstream fout("avarcolaci.out");
	fin >> t;
	while(t -- ) {
		fin >> n;
		int cnt = -1, act;
		for(int i = 1 ; i <= 2 * n ; ++ i) {
			int x;
			fin >> x;
			if(cnt == -1) {
				act = x;
				cnt = 1;
			}
			else if(act == x)
				++ cnt;
			else
				-- cnt;
		}
		elmaj.push_back(act);
	}
	fin.close();
	fin.open("avarcolaci.in");
	fin >> t;
	for(int i = 0 ; i < t ; ++ i) {
		fin >> n;
		int act = elmaj[i];
		int cnt = 0;
		for(int i = 1 ; i <= 2 * n ; ++ i) {
			int x;
			fin >> x;
			cnt += (act == x);
		}
		if(cnt >= n + 1)
			fout << act << '\n';
		else
			fout << "Mozart\n";
	}
}
