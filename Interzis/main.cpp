#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 15005;
const int maxl = 1005;
const int mod = 101267;

int dp[2][maxl], pi[maxn], n, l;
char s[maxn];

inline void buildpi() {
    int k = 0;
    for(int i = 2 ; i <= n ; ++ i) {
        while(k > 0 && s[k + 1] != s[i])
            k = pi[k];
        if(s[k + 1] == s[i])
            ++ k;
        pi[i] = k;
    }
}

int main() {
    ifstream fin("interzis.in");
    ofstream fout("interzis.out");
    fin >> n >> l >> s + 1;
    buildpi();
    dp[1][0] = 1; /// daca e a, pun b, daca e b, pun a
    dp[1][1] = 1; /// daca e a, pun a, daca e b, pun b
    for(int i = 1 ; i <= n ; ++ i) {
        memset(dp[i & 1 ^ 1], 0, sizeof(dp[i & 1 ^ 1]));
        for(int j = 0 ; j < min(i + 1, l) ; ++ j) {
            for(char op = 'a' ; op <= 'b' ; ++ op)
                if(s[j + 1] == op)
                    dp[(i & 1) ^ 1][j + 1] = (dp[(i & 1) ^ 1][j + 1] + dp[i & 1][j]) % mod;
                else {
                    int k = pi[j];
                    while(k > 0 && s[k + 1] != op)
                        k = pi[k];
                    if(s[k + 1] == op)
                        ++ k;
                    dp[(i & 1) ^ 1][k] = (dp[(i & 1) ^ 1][k] + dp[i & 1][j]) % mod;
                }
            }
    }
    int sum = 0;
    for(int i = 0 ; i < l ; ++ i)
        sum = (sum + dp[n & 1][i]) % mod;
    fout << sum << '\n';
}
