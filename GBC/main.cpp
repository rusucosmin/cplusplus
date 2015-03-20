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

const char infile[] = "gbc.in";
const char outfile[] = "gbc.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int POW = 32767;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int G[MAXN], K, N, M, bits[POW + 5];
long long comb[110][110];
int Gt[MAXN], st[10];
long long Ans;

inline int bitCount(int conf) {
    int ans = 0;
    while(conf) {
        ++ ans;
        conf &= (conf - 1);
    }
    return ans;
}

inline void buildComb(const int &_index) {
    for(int i = 0 ; i <= 31 ; ++ i) {
        comb[i][0] = 1;
        for(int j = 1 ; j <= i ; ++ j)
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
    }
}

void Back(int P) {
    if(P == N + 1) {
        int mask = G[st[1]];
        for(int i = 2 ; i < P ; ++ i)
            mask &= G[st[i]];
        Ans += 1LL * comb[bits[(mask & POW)] + bits[(mask >> 15)]][M];
        return;
    }
    for(int i = st[P - 1] + 1; i <= K ; ++ i) {
        st[P] = i;
        Back(P + 1);
    }
}

int main() {
    fin >> K >> N >> M;
    for(int i = 1 ; i <= K ; ++ i) {
        for(int j = 1 ; j <= K ; ++ j) {
            char c;
            fin >> c;
            G[i] = (G[i] << 1) + (c - '0');
        }
    }
    buildComb(M);
    for(int i = 0 ; i <= POW ; ++ i)
        bits[i] = bitCount(i);

    Back(1);

    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
