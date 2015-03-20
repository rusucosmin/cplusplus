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

const char infile[] = "unuzero.in";
const char outfile[] = "unuzero.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;
const int MOD = 666013;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, P, Q;
int dp[MAXN][MANX];

int main() {
    fin >> N >> P >> Q;
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j <= Q ; ++ j) {
            dp[i][j][0] += dp[i - 1][j][0];
            dp[i][j][0] += dp[i - 1][j][1];
            dp[i][j][0] %= MOD;
            dp[i][j][1] += dp[i - 1][j][0];
            dp[i][j][1] += dp[i - 1][j - 1][1];
            dp[i][j][1] %= MOD;
        }
    }
    int Ans = 0;
    for(int i = P ; i <= Q ; ++ i)
        Ans = (Ans + dp[N][i][0] + dp[N][i][1]) % MOD;
    fin.close();
    fout.close();
    return 0;
}
