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

const char infile[] = "frunze.in";
const char outfile[] = "frunze.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int MOD = 29989;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, P, a[55][55];

inline int Stirling(int n, int m) {
    if(m <= 1 || m == n) {
        a[n][m] = 1;
        return 1;
    }
    if(a[n][m])
        return a[n][m];
    a[n][m] = (Stirling(n - 1, m - 1) + 1LL * m * Stirling(n - 1, m) % MOD) % MOD;
    return a[n][m];
}

int main() {
    fin >> N >> P;
    int tmp = Stirling(N - 2, N - P);
    for(int i = P + 1 ; i <= N ; ++ i)
        tmp = (1LL * tmp * i) % MOD;
    fout << tmp << '\n';
    fin.close();
    fout.close();
    return 0;
}
