#include <fstream>
#include <string.h>
#include <cassert>

using namespace std;

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

int N, M, K;
char c[MAXN][MAXN];
int Prefix[MAXN][MAXN];
int similar[MAXN][MAXN];
int dp[MAXN][MAXN];

ifstream fin("zip.in");
ofstream fout("zip.out");

inline void buildPrefix(const char *P, int *Pi) {
    int k = 0;
    Pi[1] = 0;
    for(int i = 2 ; i <= K ; ++ i) {
        while(k > 0 && P[k + 1] != P[i])
            k = Pi[k];
        if(P[k + 1] == P[i])
            ++ k;
        Pi[i] = k;
    }
}

inline int KMP(const char *A, const char *B, const int *Pi) {  /// search for B in A
    int k = 0;
    for(int i = 1 ; i <= K ; ++ i) {
        while(k > 0 && B[k + 1] != A[i])
            k = Pi[k];
        if(B[k + 1] == A[i])
            ++ k;
        if(k == K)
            return K - 1;
    }
    return k;
}

int main() {
    fin >> N >> M >> K;
    fin.getline(c[0], MAXN);
    for(int i = 1 ; i <= N ; ++ i) {
        fin.getline(c[i] + 1, MAXN);
        buildPrefix(c[i], Prefix[i]);
    }
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            similar[i][j] = K - KMP(c[i], c[j], Prefix[j]); /// remaining letters
    memset(dp, oo, sizeof(dp));
    for(int i = 1 ; i <= N ; ++ i)
        dp[1][i] = K;
    for(int k = 2 ; k <= M ; ++ k)
        for(int i = 1 ; i <= N ; ++ i) {
            //dp[k][i] = min(dp[k][i], dp[k][i] + similar[i][i]);
            for(int j = 1 ; j <= N ; ++ j)
                if(i != j)
                    dp[k][i] = min(dp[k][i], dp[k - 1][j] + similar[j][i]);
            }
    int Ans = 0;
    for(int i = 1 ; i <= N ; ++ i)
        if(dp[M][Ans] >= dp[M][i])
            Ans = i;
    fout << dp[M][Ans] << '\n';
    return 0;
}
