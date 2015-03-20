#include <fstream>
#include <iomanip>

using namespace std;

pair <double, double> v[10];
int T;

int main() {
	ifstream fin("paralelogram2.in");
	ofstream fout("paralelogram2.out");
	fin >> T;
	fout << fixed << setprecision(5); 
	while (T -- ) {
		for(int i = 1 ; i <= 4 ; ++ i)
			fin >> v[i].first >> v[i].second;
		v[5] = v[1];
		for(int i = 1 ; i <= 4 ; ++ i) 
			fout << (v[i].first + v[i + 1].first) / 2 << ' ' << (v[i].second + v[i + 1].second) / 2 << ' ';
		fout << '\n';	
	}	
}
