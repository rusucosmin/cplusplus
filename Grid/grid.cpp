#include <fstream>
#include <iterator>
#include <list>
#include <iostream>

using namespace std;

list <int> v[4];
int n, k;

int main() {
	ifstream fin("grid.in");
	ofstream fout("grid.out");

	fin >> n >> k;

	for(int i = 0 ; i < 3 ; ++ i) {
		for(int j = n - 1 ; j >= 0 ; -- j) {
			v[i].push_front(i * n + j + 1);
		}
	}
	
	for(int i = 1 ; i <= k ; ++ i) {
		int x1, y1, x2, y2;
		fin >> x1 >> y1 >> x2 >> y2;
			
		list <int> :: iterator it = v[x1].begin();
		advance(it, y1);
		int nr = *it;
		v[x1].erase(it);
		it = v[x2].begin();
		advance(it, y2);

		v[x2].insert(it, nr);
	}

	for(int i = 0 ; i < 3 ; ++ i, fout << '\n')
		for(auto it :v[i])
			fout << it << ' ';


	

}
