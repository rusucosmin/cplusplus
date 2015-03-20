
#include <vector>
#include <iostream>
#include <bitset>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <string.h>

using namespace std;

const char infile[] = "auto2.in";
const char outfile[] = "auto2.out";

const int MAXN = 105;
const int MAXM = 505;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

int N, M, p[MAXN], G[MAXN][MAXN], dist[MAXM], cost[MAXM][MAXN], A, B, T;
int dp[MAXN][MAXN];
queue < pair<int, int> > Q;

inline void buildDynamic() {
    memset(dp, oo, sizeof(dp));
    /// REPLACE THIS FOR TILL T
    for(int i = 0 ; i <= T ; ++ i) {
        dp[A][i] = 0;
        Q.push(make_pair(A, i));
    }
    int Ans = oo;
    while(!Q.empty()) {
        int Node = Q.front().first;
        int time = Q.front().second;
        Q.pop();
        //printf("%d\n", Node);
        if(Node == B && time <= T) {
            Ans = min(Ans, dp[Node][time]);
            continue;
        }
        if(time > T)
            continue;
        for(int i = 1 ; i <= N ; ++ i)
            if(G[Node][i]) {
                for(int addTime = 0 ; time + addTime <= T ; ++ addTime) {
                    int newTime = time + dist[G[Node][i]] + addTime;
                    int costForThat = dist[G[Node][i]] * cost[G[Node][i]][time] + addTime * p[i];
                    if(dp[i][newTime] > dp[Node][time] + costForThat) {
                        dp[i][newTime] = dp[Node][time] + costForThat;
                        Q.push(make_pair(i, newTime));
                    }
                }
            }
    }
    printf("%d\n", Ans);
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d", &N, &M);
    scanf("%d %d %d", &A, &B, &T);
    for(int i = 1 ; i <= N ; ++ i)
        scanf("%d", &p[i]);
    p[A] = p[B] = 0;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        G[x][y] = i;
        G[y][x] = i;
        dist[i] = z;
        for(int j = 0 ; j < T ; ++ j)
            scanf("%d", &cost[i][j]);
    }
    buildDynamic();
    return 0;
}
