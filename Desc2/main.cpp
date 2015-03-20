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

const char infile[] = "desc2.in";
const char outfile[] = "desc2.out";

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

int N, K, X;
int dp[MAXN];
const int MOD = 10007;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> N >> K >> X;
    N -= (K * (K - 1) * X / 2) + K;
    dp[0] = 1;
    for(int i = 1 ; i <= K ; ++ i)
        for(int j = 0 ; j <= N - i ; ++ j)
            dp[i + j] = (dp[i + j] + dp[j]) % MOD;
    fout << dp[N] << '\n';
    fin.close();
    fout.close();
    return 0;
}
