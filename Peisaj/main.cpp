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

const char infile[] = "peisaj.in";
const char outfile[] = "peisaj.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 55;
const int MAXK = 12;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, K;
long long dp[2][MAXN / 2][2], vf[2][MAXN / 2][MAXK][2];

int main() {
    fin >> N >> K;
    dp[0][0][0] = 1;
    for(int i = 1 ; i <= N ; ++ i) {
        dp[i&1][0][0] = dp[(i&1)^1][1][0];
        dp[i&1][0][1] = dp[(i&1)^1][1][1];
        for(int j = 1 ; j <= N / 2 ; ++ j) {
            dp[i&1][j][0] = dp[(i&1)^1][j - 1][0] + dp[(i&1)^1][j + 1][0];
            if(j != K)
                dp[i&1][j][1] = dp[(i&1)^1][j - 1][1] + dp[(i&1)^1][j + 1][1];
            else dp[i&1][j][1] = dp[(i&1)^1][j - 1][0] + dp[(i&1)^1][j + 1][1];
        }
    }
    vf[0][1][0][0] = 1;
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j <= N / 2 ; ++ j)
            for(int v = 0 ; v <= K ; ++ v) {
                vf[i&1][j][v][0] = vf[(i&1)^1][j - 1][v][0] + vf[(i&1)^1][j][v][1];
                vf[i&1][j][v][1] = vf[(i&1)^1][j + 1][v][1] + vf[(i&1)^1][j][v - 1][0];
            }
    }
    fout << dp[N & 1][0][0] << ' ' << dp[N & 1][0][1] << ' ' << vf[(N - 1)&1][1][K][1] << '\n';
    fin.close();
    fout.close();
    return 0;
}
