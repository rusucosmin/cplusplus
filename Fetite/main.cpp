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

const char infile[] = "fetite.in";
const char outfile[] = "fetite.out";

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

unsigned long long findPetal(const unsigned long long &N) {
    if(N == 1)
        return 1;
    /// 123456789
    /// 13579
    if(N & 1)
        return 2 * findPetal((N - 1) / 2) + 1;
    return 2 * findPetal(N / 2) - 1;
}

int main() {
    unsigned long long N;
    fin >> N;
    fout << findPetal(N) << '\n';
    fin.close();
    fout.close();
    return 0;
}
