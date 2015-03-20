#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

const int mod = 9967;
const int maxd = 1002;
const int sigma = 26;

int n, d;
int  dp[maxd];

inline void dei(int n, int dp[maxd]) {
    if(n == 1) {
        for(int i = 0 ; i < sigma ; ++ i)
            ++ dp[i % d];
        return ;
    }
    int dp1[maxd], dp2[maxd];
    memset(dp1, 0, sizeof(dp1));
    memset(dp2, 0, sizeof(dp2));
    int maxi = d;
    if(n & 1) {
        dei(n - 1, dp1);
        dei(1, dp2);
        maxi = sigma;
    }
    else {
        dei(n / 2, dp1);
        memcpy(dp2, dp1, sizeof(dp2));
    }
    for(int j1 = 0 ; j1 < d ; ++ j1)
        for(int j2 = 0 ; j2 < maxi ; ++ j2) {
            int sum = j1 + j2;
            if(sum >= d)
                sum -= d;
            dp[sum] = dp[sum] + dp1[j1] * dp2[j2];
            dp[sum] %= mod;
        }
}

int main() {
    ifstream fin("cuvinte2.in");
    ofstream fout("cuvinte2.out");
    fin >> n >> d;
    dei(n, dp);
    fout << dp[0] << '\n';
}
