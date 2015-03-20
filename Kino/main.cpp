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
#include <unordered_map>

using namespace std;

const char infile[] = "kino.in";
const char outfile[] = "kino.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 20005;
const int MAXL = 55;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, L, k[MAXL], a[MAXN][MAXL], fr[MAXN], ind[MAXN];

class comp {
public:
    inline bool operator () (const int &a, const int &b) const {
        return fr[a] < fr[b];
    }
};

unordered_map<int, int> frbig;

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getInt(int &x) {
    x = 0;
    while(!isdigit(buff[pos])) {
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
    while(isdigit(buff[pos])) {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

int main() {
    freopen(infile, "r", stdin);
    getInt(N);
    getInt(L);
    for(int i = 0 ; i < L ; ++ i)
        getInt(k[i]);
    for(int i = 0 ; i < N ; ++ i) {
        for(int j = 0 ; j < L ; ++ j) {
            getInt(a[i][j]);
        }
    }
    long long ans = (1LL * L * N * (N - 1)) / 2LL;
    for(int j = 0 ; j < L ; ++ j) {
        memset(fr, 0, sizeof(fr));
        int pos = 0;
        frbig.clear();
        int u = 0;
        for(int i = 0 ; i < N ; ++ i) {
            if(i + 1 <= k[j])
                ind[++ u] = i + 1;
            if(!a[i][j]) {
                ++ pos;
                continue;
            }
            if(a[i][j] <= N)
                ++ fr[a[i][j]];
            else
                ++ frbig[a[i][j]];
        }
        sort(ind + 1, ind + u + 1, comp());
        int index = 1;
        for(int i = 0 ; i < pos ; ++ i) {
            ++ fr[ind[index]];
            if(index == u || fr[ind[index + 1]] >= fr[ind[1]])
                index = 1;
            else ++ index;
        }
        for(int i = 1 ; i <= N ; ++ i)
            ans -= ((1LL * fr[i] * (fr[i] - 1)) / 2LL);
        for(unordered_map<int, int> :: iterator it = frbig.begin(); it != frbig.end(); ++ it)
            ans -= ((1LL * it->second * (it->second - 1)) / 2LL);
    }
    fout << ans;
    fin.close();
    fout.close();
    return 0;
}
