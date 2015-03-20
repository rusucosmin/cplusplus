#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int NMAX = 4097, PMAX = 260, EDGEMAX = 65536;

int N, M, X[EDGEMAX + 1], Y[EDGEMAX + 1], Adj[NMAX][PMAX], Cnt[65537], Group, Index, Ans;

int main()
{
    freopen("triplete.in", "r", stdin);
    freopen("triplete.out", "w", stdout);

    scanf("%i %i", &N, &M);
    for(int i = 1; i <= M; ++ i)
    {
        scanf("%i %i", &X[i], &Y[i]);
        X[i] --;
        Y[i] --;

        Group = Y[i] / 16, Index = Y[i] % 16;
        Adj[X[i]][Group] |= (1 << Index);

        Group = X[i] / 16, Index = X[i] % 16;
        Adj[Y[i]][Group] |= (1 << Index);
    }

    for(int i = 1; i <= 65536; ++ i)
        Cnt[i] = Cnt[i >> 1] + (i & 1);

    for(int i = 1; i <= M; ++ i)
        for(int j = 0; j <= N / 16; ++ j)
            Ans += Cnt[ Adj[X[i]][j] & Adj[Y[i]][j] ];

    printf("%i\n", Ans / 3);

    return 0;
}
