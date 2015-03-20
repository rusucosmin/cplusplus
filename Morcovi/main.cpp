#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxn = 1000;
const int maxp = 12;

unsigned int dp[1 << maxp][maxn];
int n, p, jumps[maxp], v[maxn];

int main() {
    ifstream fin("morcovi.in");
    ofstream fout("morcovi.out");
    fin >> n;
    for(int i = 0 ; i < n ; ++ i) {
        fin >> v[i];
        dp[0][i] = v[i];
    }
    fin >> p;
    for(int i = 0 ; i < p ; ++ i)
        fin >> jumps[i];
    int maxmask = 1 << p;
    for(int conf = 0 ; conf < maxmask ; ++ conf)
        for(int i = 0 ; i < p ; ++ i)
            if(conf & (1 << i))
                for(int j = 0 ; j < n ; ++ j) {
                    unsigned int &act = dp[conf][j];
                    if(j - jumps[i] >= 0)
                        act = max(act, dp[conf ^ (1 << i)][j - jumps[i]] + v[j]);
                    if(j + jumps[i] < n)
                        act = max(act, dp[conf ^ (1 << i)][j + jumps[i]] + v[j]);
                }
    unsigned int ans = 0;
    for(int i = 0 ; i < n ; ++ i)
        ans = max(ans, dp[maxmask - 1][i]);
    fout << ans << '\n';
}
