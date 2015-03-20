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

const char infile[] = "plantatie.in";
const char outfile[] = "plantatie.out";

ofstream fout(outfile);

const int MAXN = 505;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, Q, RMQ[10][MAXN][MAXN], Lg[MAXN];

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void get(int &x) {
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9')) {
        if(++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    }
}

int main() {
    freopen(infile, "r", stdin);
    get(N);
    get(Q);
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            get(RMQ[0][i][j]);
    for(int i = 2 ; i <= N ; ++ i)
        Lg[i] = Lg[i >> 1] + 1;
    for(int k = 1 ; (1 << k) <= N ; ++ k)
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= N ; ++ j) {
                int l = (1 << (k - 1));
                RMQ[k][i][j] = max(RMQ[k - 1][i][j],
                                   max(RMQ[k - 1][i + l][j + l],
                                       max(RMQ[k - 1][i][j + l],
                                           RMQ[k - 1][i + l][j])));
            }
    for(int i = 1 ; i <= Q ; ++ i) {
        int x, y, z;
        get(x);
        get(y);
        get(z);
        int lg = Lg[z];
        fout << max(RMQ[lg][z + x - (1 << lg)][z + y - (1 << lg)],
                    max(RMQ[lg][x][y],
                        max(RMQ[lg][z + x - (1 << lg)][y],
                            RMQ[lg][x][z + y - (1 << lg)]))) << '\n';
    }
    fout.close();
    return 0;
}
