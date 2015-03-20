#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
	ofstream fout("fenrir.out");
	srand(time(NULL));
	fout << 83 << '\n';
	for(int i = 16 ; i <= 20 ; ++ i)
		fout << i << ' ' << 7 << '\n';
	fout << "3 8\n";
	fout << "5 15\n";
	for(int i = 1 ; i <= 6 ; ++ i)
		for(int j = i + 1 ; j <= 7 ; ++ j)
			fout << i << ' ' << j << '\n';
	for(int i = 8 ; i <= 13 ; ++ i)
		for(int j = i + 1 ; j <= 14 ; ++ j)
			fout << i << ' ' << j << '\n';
	for(int i = 15 ; i <= 19 ; ++ i)
		for(int j = i + 1 ; j <= 20 ; ++ j)
			fout << i << ' ' << j << '\n';
	fout << "1 8\n1 9\n1 10\n1 11\n1 12\n2 15\n2 16\n2 17\n2 18\n3 15\n3 16\n3 17\n3 18\n4 15\n4 16\n4 17\n4 18\n5 15\n5 16";
}
