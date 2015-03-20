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

const int MAXN = 105;
const int MOD = 100;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int a[MAXN], N, sum[MAXN][MAXN], dp[MAXN][MAXN];

inline int memo(int st, int dr) {
    if(st == dr)
        dp[st][dr] = 0;
    if(st + 1 == dr)
        dp[st][dr] = a[st] * a[dr];
    if(dp[st][dr] != oo)
        return dp[st][dr];
    for(int i = st ; i + 1 <= dr ; ++ i)
        dp[st][dr] = min(dp[st][dr], sum[st][i] * sum[i + 1][dr] + memo(st, i) + memo(i + 1, dr));
    return dp[st][dr];
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(cin >> N) {
        for(int i = 1 ; i <= N ; ++ i)
            cin >> a[i];
        for(int i = 1 ; i <= N ; ++ i) {
            sum[i][i] = a[i];
            for(int j = i + 1 ; j <= N ; ++ j) {
                sum[i][j] = sum[i][j - 1] + a[j];
                if(sum[i][j] >= 100)
                    sum[i][j] -= 100;
            }
        }
        memset(dp, oo, sizeof(dp));
        cout << memo(1, N) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
