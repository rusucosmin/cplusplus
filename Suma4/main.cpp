#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

ifstream fin("suma4.in");
ofstream fout("suma4.out");

const int maxn = 65005;
const int maxk = 60;
const int oo = 0x3f3f3f3f;

const int dz[] = {1, 1, 1, 1};
const int dx[] = {0, 0, 1, 1};
const int dy[] = {0, 1, 0, 1};

int n, k, a[maxn], dp[maxk][maxk][maxk], ind[maxk][maxk][maxk];

inline void write(int niv, int x, int y) {
    if(niv == k + 1)
        return ;
    fout << ind[niv][x][y] << ' ';
    for(int d = 0 ; d < 4 ; ++ d) {
        int newk = niv + dz[d];
        int newx = x + dx[d];
        int newy = y + dy[d];
        if(dp[niv][x][y] == dp[newk][newx][newy] + a[ind[niv][x][y]]) {
            write(newk, newx, newy);
            return;
        }
    }
}

int main() {
    fin >> n;
    int cnt = 0;
    for(k = 0 ; cnt < n ; ) {
        ++ k;
        for(int i = 1 ; i <= k ; ++ i)
            for(int j = 1 ; j <= k ; ++ j) {
                ++ cnt;
                fin >> a[cnt];
                ind[k][i][j] = cnt;
                dp[k][i][j] = oo;
            }
    }
    for(int i = 1 ; i <= k ; ++ i)
        for(int j = 1 ; j <= k ; ++ j)
            dp[k][i][j] = a[ind[k][i][j]];
    for(int niv = k - 1 ; niv >= 1 ; -- niv)
        for(int i = 1 ; i <= k ; ++ i)
            for(int j = 1 ; j <= k ; ++ j)
                for(int d = 0 ; d < 4 ; ++ d) {
                    int newk = niv + dz[d];
                    int newy = j + dy[d];
                    int newx = i + dx[d];
                    dp[niv][i][j] = min(dp[niv][i][j], a[ind[niv][i][j]] + dp[newk][newx][newy]);
                }
    fout << k << ' ' << dp[1][1][1] << '\n';
    write(1, 1, 1);
}
