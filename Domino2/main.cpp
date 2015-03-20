#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "domino2.in";
const char outfile[] = "domino2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;

inline void Solve(const int &p) {
    fout << 2*p - 1 << ' ' << 2*p << '\n';
	fout << 2*p << " 1\n";
	fout << 1 << ' ' << 2*p+1 << '\n';
	fout << 2*p+1<<' '<<2<<'\n';
	for(int i=1; i<p-1; ++i) {
		fout << 2*i << ' ' << 2*p << '\n';
		fout << 2*p << ' ' << 2*i+1 << '\n';
		fout << 2*i+1 << ' ' << 2*p+1 << '\n';
		fout << 2*p+1 << ' ' << 2*i+2 << '\n';
	}
	fout << 2*p-2 << ' ' << 2*p << '\n';
	fout << 2*p << ' ' << 2*p << '\n';
	fout << 2*p << ' ' << 2*p+1 << '\n';
	fout << 2*p+1 << ' ' << 2*p+1 << '\n';
	if(2*p+1 < N) Solve(p+1);
	fout << 2*p+1 << ' ' << 2*p-1 << '\n';
}

int main() {
    fin >> N;
    if(N == 1) {
        fout << "1 1\n";
        return 0;
    }
    if(N == 2) {
        fout << "1 1\n1 2\n2 2";
        return 0;
    }
    if(!(N & 1)) {
        fout << "-1\n";
        return 0;
    }
    fout << "3 3\n3 1\n1 1\n1 2\n2 2\n2 3\n";
    if(N > 3)
        Solve(2);
    fin.close();
    fout.close();
    return 0;
}
