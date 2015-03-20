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

const char infile[] = "intersort.in";
const char outfile[] = "intersort.out";

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

int N, aib[MAXN], a[MAXN];

inline int lsb(int conf) {
    return conf & (-conf);
}

inline void Update(int pos) {
    for(int _pos = pos ; _pos <= N ; _pos += lsb(_pos))
        ++ aib[_pos];
}

inline int Query(int pos) {
    int _sum = 0;
    for(int _pos = pos ; _pos > 0 ; _pos -= lsb(_pos))
        _sum += aib[_pos];
    return _sum;
}

int main() {
    fin >> N;
    long long Ans = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> a[i];
        Ans += 1LL * a[i] * (Query(N) - Query(a[i] - 1));
        Update(a[i]);
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
