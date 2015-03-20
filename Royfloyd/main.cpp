#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("royfloyd.in");
ofstream fout("royfloyd.out");

const int maxn = 105;
const int oo = 0x3f3f3f3f;

int n, dp[maxn][maxn];

int main() {
    fin >> n;
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= n ; ++ j) {
            fin >> dp[i][j];
            if(!dp[i][j] && i != j)
                dp[i][j] = oo;
        }
    for(int k =  1 ; k <= n ; ++ k)
        for(int i = 1 ; i <= n ; ++ i)
            for(int j = 1 ; j <= n ; ++ j)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
    for(int i = 1 ; i <= n ; ++ i, fout << '\n')
        for(int j = 1 ; j <= n ;++ j) {
            if(dp[i][j] == oo)
                dp[i][j] = 0;
            fout << dp[i][j] << ' ';
        }
}
