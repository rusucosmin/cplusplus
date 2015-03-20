#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "namlei.in";
const char outfile[] = "namlei.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 30001;
const int oo = 0x3f3f3f3f;
const int MAXK = 8;
const int MOD = 997;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

int N, K, X, Y;
short m[MAXN][MAXK][MAXK], Ans[MAXK][MAXK], aux[MAXK][MAXK];
short aint[MAXN * 3][MAXK][MAXK];
short mod[1000000];

inline void Multiply(short a[MAXK][MAXK], short b[MAXK][MAXK], short c[MAXK][MAXK]) {
    memset(c, 0, sizeof(m[0]));
    for(int k = 0 ; k < K ; ++ k)
        for(int i = 0 ; i < K ; ++ i)
            for(int j = 0 ; j < K ; ++ j)
                c[i][j] = mod[(c[i][j] + a[i][k] * b[k][j])];
}

inline void Build(int Node, int st, int dr) {
    if(st == dr) {
        memcpy(aint[Node], m[st], sizeof(m[st]));
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(Node << 1, st, mid);
    Build((Node << 1) | 1, mid+1, dr);
    Multiply(aint[Node << 1], aint[(Node << 1) | 1], aint[Node]);
}

inline void Update(int Node, int st, int dr, int pos) {
    if(st == dr) {
        memcpy(aint[Node], m[st], sizeof(m[st]));
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(Node << 1, st, mid, pos);
    else Update((Node << 1) | 1, mid+1, dr, pos);
    Multiply(aint[Node << 1], aint[(Node << 1) | 1], aint[Node]);
}

inline void Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b) {
        Multiply(Ans, aint[Node], aux);
        memcpy(Ans, aux, sizeof(aux));
        return;
    }
    int mid = ((st + dr) >> 1);
    if(a <= mid)
        Query((Node << 1), st, mid, a, b);
    if(mid < b)
        Query((Node << 1) | 1, mid+1, dr, a, b);
}

int main() {
    fin >> N >> K >> X >> Y;
    for(int i=1; i<1000000; ++i) {
        mod[i]=mod[i-1]+1;
        if(mod[i]>=997) mod[i]-=997;
    }
    for(int i = 0 ; i < N ; ++ i) {
        for(int obj1 = 0 ; obj1 < K ; ++ obj1)
            for(int obj2 = 0 ; obj2 < K ; ++ obj2)
                m[i][obj1][obj2] = 1;
        int cnt, j, k;
        fin >> cnt >> j >> k;
        int pk, pj;
        for(int w = 1 ; w <= cnt ; ++ w) {
            ++ m[i][j][k];
            pj = j;
            pk = k;
            j = (pj * X + pk * w * Y) % K;
            k = (pj * w * X + pk * Y) % K;
        }
    }
    Build(1, 0, N - 1);
    for(char op ; fin >> op ; ) {
        if(op == 'U') {
            int i, cnt, j, k;
            fin >> i >> cnt >> j >> k;
            for(int obj1 = 0 ; obj1 < K ; ++ obj1)
                for(int obj2 = 0 ; obj2 < K ; ++ obj2)
                    m[i][obj1][obj2] = 1;
                    int pk, pj;
            for(int w = 1 ; w <= cnt ; ++ w) {
                ++ m[i][j][k];
                pj = j;
                pk = k;
                j = (pj * X + pk * w * Y + 1) % K;
                k = (pj * w * X + pk * Y + 1) % K;
            }
            Update(1, 0, N - 1, i);
        }
        if(op == 'Q') {
            int i, x, y, j;
            fin >> i >> x >> j >> y;
            -- j;
            memset(Ans, 0, sizeof(Ans));
            for(int l = 0 ; l < K ; ++ l)
                Ans[l][l] = 1;
            Query(1, 0, N - 1, i, j);
            fout << Ans[x][y] << '\n';
        }
    }
    fout.close();
    return 0;
}
