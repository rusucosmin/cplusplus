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

const char infile[] = "input.in";
const char outfile[] = "output.out";

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

int dp[2][MAXN], w[MAXN], N, M, p[MAXN];

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(cin >> M >> N) {
        if(!N && !M)
            return 0;
        for(int i = 1 ; i <= N ; ++ i)
            cin >> w[i] >> p[i];
        memset(dp, 0, sizeof(dp));
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 0 ; j <= M ; ++ j) {
                dp[i & 1][j] = dp[i & 1 ^ 1][j];
                if(j - w[i] >= 0)
                    dp[i & 1][j] = max(dp[i & 1][j], dp[i & 1 ^ 1][j - w[i]] + p[i]);
            }
        for(int j = 0 ; j <= M ; ++ j)
            if(dp[N & 1][j] == dp[N & 1][M]) {
                cout << j << ' ' << dp[N & 1][j] << '\n';
                break;
            }
    }
    fin.close();
    fout.close();
    return 0;
}
