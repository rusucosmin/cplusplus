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

const char infile[] = "retea3.in";
const char outfile[] = "retea3.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1010;
const int oo = 0x3f3f3f3f;
const int MOD = 666013;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int dp[2][MAXN], N, M;

inline int lgPow(int a, int n) {
    int ans = 1;
    for( ; n ; n >>= 1) {
        if(n & 1)
            ans = (1LL * ans * a) % MOD;
        a = (1LL * a * a) % MOD;
    }
    return ans;
}

int main() {
    fin >> N >> M;
    dp[1 & 1][1] = 2;
    for(int i = 2 ; i <= M ; ++ i)
        dp[1 & 1][i] = (2LL * dp[1 & 1][i - 1]) % MOD;
    for(int i = 2 ; i <= M ; ++ i) {
        dp[i & 1][1] = (2LL * dp[(i & 1) ^ 1][1]) % MOD;
        for(int j = 2 ; j <= M ; ++ j)
            dp[i & 1][j] = (2LL * (dp[(i & 1) ^ 1][j] + dp[i & 1][j - 1] - dp[(i & 1) ^ 1][j - 1] + MOD) % MOD) % MOD;
    }
    fout << lgPow(dp[M & 1][M], N - 1);
    fin.close();
    fout.close();
    return 0;
}
