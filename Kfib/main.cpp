#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

ifstream fin("kfib.in");
ofstream fout("kfib.out");

const int maxn = 100005;
const int mod = 666013;

inline void multiply(int a[2][2], int b[2][2], int c[2][2]) {
    for(int i = 0 ; i < 2 ; ++ i)
        for(int j = 0 ; j < 2 ; ++ j)
            for(int k = 0 ; k < 2 ; ++ k)
                a[i][j] = (a[i][j] + 1LL * b[i][k] * c[k][j]) % mod;
}

inline void kfib(int k) {
    int a[2][2] = {
        {0, 1},
        {1, 1}
    };
    int ans[2][2] = {
        {1, 0},
        {0, 1}
    };
    int aux[2][2];
    for( ; k ; k >>= 1) {
        if(k & 1) {
            memset(aux, 0, sizeof(aux));
            multiply(aux, ans, a);
            memcpy(ans, aux, sizeof(aux));
        }
        memset(aux, 0, sizeof(aux));
        multiply(aux, a, a);
        memcpy(a, aux, sizeof(aux));
    }
    fout << ans[1][1] << '\n';
}

int main() {
    int k;
    fin >> k;
    kfib(k - 1);
}
