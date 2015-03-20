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

const char infile[] = "puncte2.in";
const char outfile[] = "puncte2.out";

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

inline unsigned long long getAns(int N) {
    if(N < 4)
        return 0;
    /// c(n, k) / N ! / K! * (n - k) !
    /// c(n, 4) = N! / (4! * (N -4 ) !;
    /// = (N - 3) * (N - 2) * (N - 1) * N / 4!
    /// 1 * 2 * 3 * 4 = 3 * 8 = 24
    return 1ULL * N * (N - 1) * (N - 2) * (N - 3) / 24ULL;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int N;
    fin >> N;
    fout << getAns(N) << '\n';
    fin.close();
    fout.close();
    return 0;
}
