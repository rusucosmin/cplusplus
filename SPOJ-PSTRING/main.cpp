#include <fstream>
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

const int maxx = 10005;
const int maxy = 1005;
const int oo = 0x3f3f3f3f;

char x[maxx], y[maxy];
int n, m, pi[maxy], nxt[maxy][26], dp[maxx][maxy];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin.getline(x + 1, maxx);
    cin.getline(y + 1, maxy);
    n = strlen(x + 1);
    m = strlen(y + 1);
    int k = 0;
    for(int i = 2 ; i <= m ; ++ i) {
        while(k > 0 && y[k + 1] != y[i])
            k = pi[k];
        if(y[k + 1] != y[i])
            ++ k;
        pi[i] = k;
    }
    for(int i = 0 ; i <= m ; ++ i) {
        for(char ch = 'a' ; ch <= 'z' ; ++ ch) {
            k = i;
            while(k > 0 && y[k + 1] != ch)
                k = pi[k];
            if(y[k + 1] == ch)
                ++ k;
            nxt[i][ch - 'a'] = k;
        }
    }
    memset(dp, oo, sizeof(dp));
    for(int i = 0 ; i <= m ; ++ i)
        dp[0][i] = 0;
    for(int i = 0 ; i < n ; ++ i)
        for(int j = 0 ; j <= m ; ++ j) {
            int nxtstate = nxt[j][x[i] - 'a'];
            dp[i + 1][j] = min(dp[i + 1][j], 1 + dp[i][j]);
            dp[i + 1][nxtstate] = min(dp[i + 1][nxtstate], dp[i][j]);
        }
    cout << dp[n][0] << '\n';
}
