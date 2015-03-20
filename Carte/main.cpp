#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 3005;
const int oo = 0x3f3f3f3f;

int t, n, pi[maxn], w, m, dp[maxn];
char x[maxn], s[maxn];
bitset <maxn> match[maxn];

inline void buildprefix() {
    int k = 0;
    m = strlen(x + 1);
    for(int i = 2 ; i <= m ; ++ i) {
        while(k > 0 && x[k + 1] != x[i])
            k = pi[k];
        if(x[k + 1] == x[i])
            ++ k;
        pi[i] = k;
    }
}

inline void kmp() {
    int k = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        while(k > 0 && x[k + 1] != s[i])
            k = pi[k];
        if(x[k + 1] == s[i])
            ++ k;
        if(k == m) {
            match[i - k + 1][i - k + m] = 1;
            k = pi[k];
        }
    }
}

int main() {
    ifstream fin("carte.in");
    ofstream fout("carte.out");

    fin >> t;
    fin.get();
    while(t -- ) {
        fin.getline(s + 1, maxn);
        n = strlen(s + 1);
        fin >> w;
        fin.get();
        for(int i = 1 ; i <= w ; ++ i) {
            fin.getline(x + 1, maxn);
            buildprefix();
            kmp();
        }
        memset(dp, oo, sizeof(dp));
        dp[0] = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            dp[i] = min(dp[i], dp[i - 1] + 1);
            for(int j = 1 ; j <= i ; ++ j)
                if(match[j][i])
                    dp[i] = min(dp[i], dp[j - 1]);
        }
        fout << dp[n] << '\n';
        for(int i = 1 ; i <= n ;++ i)
            match[i].reset();
    }

}
