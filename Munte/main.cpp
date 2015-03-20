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

const char infile[] = "munte.in";
const char outfile[] = "munte.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 55;
const int MAXK = 55;
const int MAXD = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

unsigned long long dp[MAXD][MAXN][MAXK][2];
int N, D, K, H[MAXK];

int main() {
    int t = 0;
    fin >> N >> D >> K;
    for(int i = 1 ; i <= K ; ++ i)
        fin >> H[i];
    if(H[1] == 0)
        t = 1;
    dp[0][0][0][0] = 1;
    dp[0][0][t][0] = 1;
    for(int i = 1; i <= D ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            for(int k = 0 ; k <= K ; ++ k) {
                if(k && H[k] == j)
                    t = k - 1;
                else t = k;
                if(j != N)
                    dp[i][j][k][0] = dp[i - 1][j][t][0] + dp[i - 1][j - 1][t][0] + dp[i - 1][j + 1][t][0];
                dp[i][j][k][1] = dp[i - 1][j][t][1] + dp[i - 1][j - 1][t][1] + dp[i - 1][j + 1][t][1];
                if(j == N)
                    dp[i][j][k][1] += dp[i - 1][j - 1][t][0];
            }
    if(K && H[K] == 0)
        -- K;
    fout << dp[D - 1][1][K][1] << '\n';
    fin.close();
    fout.close();
    return 0;
}
