#include <fstream>
#include <iostream>
#include <deque>
#include <string.h>
using namespace std;

const char infile[] = "stalpi2.in";
const char outfile[] = "stalpi2.out";

const int MAXN = 51;
const int oo = 0x3f3f3f3f;

int dp[MAXN][10005], d[MAXN], N, E;
deque <int> dq;

inline int abs(int x) {
    return max(x, -x);
}

inline bool Check(int D) {
    deque <int>().swap(dq);
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 0 ; j <= d[N] ; ++ j)
            dp[i][j] = oo;
    dp[1][0] = 0;
    for(int i = 2 ; i <= N ; ++ i) {
        for(int j = 0 ; j <= d[N] ; ++ j) {
            while(!dq.empty() && abs(j - dq.front()) > D)
                dq.pop_front();
            while(!dq.empty() && dp[i - 1][dq.back()] >= dp[i - 1][j])
                dq.pop_back();
            dq.push_back(j);
            dp[i][j] = dp[i - 1][dq.front()] + abs(d[i] - j);
        }
    }
    return dp[N][d[N]] <= E;
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d", &N, &E);
    for(int i = 2 ; i <= N ; ++ i)
        scanf("%d", &d[i]);
    int li = 0, ls = 10000, Ans = d[N];
    while(li <= ls) {
        int mid = ((li + ls) >> 1);
        if(Check(mid)) {
            ls = mid - 1;
            Ans = mid;
        }
        else li = mid + 1;
    }
    printf("%d\n", Ans);
    return 0;
}
