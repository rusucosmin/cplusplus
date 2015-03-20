#include <iostream>
#include <fstream>
#include <string.h>
#include <bitset>

using namespace std;

ifstream fin("tastatura.in");
ofstream fout("tastatura.out");

const int oo = 0x3f3f3f3f;
const int maxn = 1005;

int n, m, pi[maxn], dp[maxn];
char s[maxn], a[maxn];
bitset <maxn> match[maxn];

int main() {
    fin.getline(s + 1, maxn);
    n = strlen(s + 1);
    int cnt;
    fin >> cnt;
    fin.get();
    while(cnt --) {
        fin.getline(a + 1, maxn);
        m = strlen(a + 1);
        int k = 0;
        for(int i = 2 ; i <= m ; ++ i) {
            while(k > 0 && a[k + 1] != a[i])
                k = pi[k];
            if(a[k + 1] == a[i])
                ++ k;
            pi[i] = k;
        }
        k = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            while(k > 0 && a[k + 1] != s[i])
                k = pi[k];
            if(a[k + 1] == s[i])
                ++ k;
            if(k == m) {
                match[i - m + 1][i] = 1;
                k = pi[k];
            }
        }
    }
    memset(dp, oo, sizeof(dp));
    dp[0] = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        dp[i] = min(dp[i], dp[i - 1] + 1);
        for(int j = 1 ; j <= i ; ++ j)
            if(match[j][i])
                dp[i] = min(dp[i], dp[j - 1] + 1);
    }
    fout << dp[n] << '\n';
}
