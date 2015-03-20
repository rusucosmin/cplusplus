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

const char infile[] = "cal.in";
const char outfile[] = "cal.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

inline int ManhattanDistance(int x1, int y1, int x2, int y2) {
    return max(x1 - x2, x2 - x1) + max(y1 - y2, y2 - y1);
}

int main() {
    int SX, SY, N, S;
    fin >> SX >> SY;
    fin >> S >> N;
    int Ans = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        int x, y;
        fin >> x >> y;
        if(ManhattanDistance(x, y, SX, SY) == S)
            ++ Ans;
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
