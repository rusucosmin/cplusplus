#include <iostream>
#include <fstream>
#include <algorithm>
#include <fstream>

#define Unu(conf, poz) ((conf) & (1 << (poz)))
#define Out(conf, poz) ((conf) ^ (1 << (poz)))

using namespace std;

ifstream fin("ture.in");
ofstream fout("ture.out");

const int Nmax = 15;
const int Mmax = 255;
const int Cmax = (1 << 15);

long long N, M, K, P, confmax, where, DP[2][Cmax + 10], Nr[Cmax + 10];
bool mat[Nmax][Mmax], change;

int main()
{
    fin >> N >> M >> K >> P;
    if(N > M) swap(N, M), change = 1;
    confmax = (1 << N);

    for(int conf = 1; conf < confmax; conf++)
        Nr[conf] = Nr[conf & (conf - 1)] + 1;

    for(int i=1; i <= P; i++)
    {
        int x, y; fin >> x >> y;
        if(change) mat[--y][--x] = 1;
        else mat[--x][--y] = 1;
    }

    for(int i=0; i < N; i++)
        if(!mat[i][0]) DP[0][(1 << i)] = 1;

    for(int j=1, t = 0; j < M; j++, t = 1-t)
    {
        for(int conf = 0; conf < confmax; conf++)
        {
            DP[1-t][conf] = DP[t][conf];
            for(int k=0; k < N; k++)
                if(Unu(conf, k) && !mat[k][j])
                {
                    DP[1-t][conf] += DP[t][Out(conf, k)];
                    if(Out(conf, k) == 0) DP[1-t][conf] += 1;
                }
        }
        where = 1-t;
    }

    long long sol = 0;
    for(int conf = 0; conf < confmax; conf++)
        if(Nr[conf] == K)
            sol += DP[where][conf];
    fout<<sol;
    return 0;
}
