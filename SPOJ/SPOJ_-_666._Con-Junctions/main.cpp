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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;
const int MOD = 10007;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, M, dp[MAXN][2], cnt[MAXN][2];
Graph G;

void DFs(int Node, int Father) {
    int with = 1, without = 0;
    int withCnt = 1, withoutCnt = 1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        DFs(*it, Node);
        with += dp[*it][1];
        withCnt = (1LL * withCnt * cnt[*it][1]) % MOD;
        without += dp[*it][0];
        withoutCnt = (1LL * withoutCnt * cnt[*it][0]) % MOD;
    }
    dp[Node][0] = with;
    cnt[Node][0] = withCnt;
    dp[Node][1] = min(with, without);
    if(with < without)
        cnt[Node][1] = withCnt;
    else if(with == without)
        cnt[Node][1] = (withoutCnt + withCnt) % MOD;
    else cnt[Node][1] = withoutCnt;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d", &T);
    for(int test = 1; test <= T ; ++ test) {
        scanf("%d", &N);
        for(int i = 1 ; i != N ; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            G[x].push_back(y);
            G[y].push_back(x);
        }
        DFs(1, 0);
        printf("%d %d\n", dp[1][1], cnt[1][1]);
        for(int i = 1 ; i <= N ; ++ i) {
            vector <int> ().swap(G[i]);
            dp[i][0] = dp[i][1] = 0;
            cnt[i][0] = cnt[i][0] = 0;
        }
    }
    return 0;
}
