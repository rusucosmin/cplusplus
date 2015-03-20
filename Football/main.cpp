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

const char infile[] = "football.in";
const char outfile[] = "football.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 30;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long dp[MAXN];
int T;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    dp[0] = 1;
    for(int i = 1 ; i < MAXN ; ++ i) {
        long long &d = dp[i];
        if(i >= 1)
            d += dp[i - 1];
        if(i >= 2)
            d += dp[i - 2];
        if(i >= 3)
            d += dp[i - 3];
        if(i >= 6)
            d += dp[i - 6];
    }
    fin >> T;
    for(int i = 1 ; i <= T ; ++ i) {
        int s;
        fin >> s;
        fout << "Case " << i << ": " << dp[s] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
