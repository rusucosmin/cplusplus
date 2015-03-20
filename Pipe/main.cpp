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

const char infile[] = "pipe.in";
const char outfile[] = "pipe.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 32005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, xst, yst, xfn, yfn;
int hor[2][2*MAXN], ver[2][2*MAXN], H, V;

int main() {
    fin >> N >> xst >> yst >> xfn >> yfn;
    memset(hor[0], oo, sizeof(hor[0]));
    memset(ver[0], oo, sizeof(ver[0]));
    hor[0][MAXN + xst] = 0;
    ver[0][MAXN + yst] = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        char color; int sz;
        fin >> color >> sz;
        if(color == 'R') {
            ++ V;
            memset(ver[V & 1], oo, sizeof(ver[V & 1]));
            for(int j = -MAXN ; j < MAXN ; ++ j) {
                j += MAXN;
                ver[V & 1][j] = ver[(V & 1) ^ 1][j]; /// decide not to take i-th piece
                if(j - sz >= 0 && ver[(V & 1) ^ 1][j - sz] + sz < ver[V & 1][j]) {
                    ver[V & 1][j] = ver[(V & 1) ^ 1][j - sz] + sz;
                }
                if(j + sz < 2*MAXN && ver[(V & 1) ^ 1][j + sz] + sz < ver[V & 1][j])
                    ver[V & 1][j] = ver[(V & 1) ^ 1][j + sz] + sz;
                j -= MAXN;
            }
        }
        if(color == 'A') {
            ++ H;
            memset(hor[H & 1], oo, sizeof(hor[H & 1]));
            for(int j = -MAXN ; j < MAXN ; ++ j) {
                j += MAXN;
                hor[H & 1][j] = hor[(H & 1) ^ 1][j]; /// decide not to take i-th piece
                if(hor[(H & 1) ^ 1][j - sz] + sz < hor[H & 1][j])
                    hor[H & 1][j] = hor[(H & 1) ^ 1][j - sz] + sz;
                if(j + sz < 2*MAXN && hor[(H & 1) ^ 1][j + sz] + sz < hor[H & 1][j])
                    hor[H & 1][j] = hor[(H & 1) ^ 1][j + sz] + sz;
                j -= MAXN;
            }
        }
    }
    if(hor[H & 1][MAXN + xfn] == oo || ver[V & 1][MAXN + yfn] == oo)
        fout << "imposibil\n";
    else
        fout << hor[H & 1][MAXN + xfn] + ver[V & 1][MAXN + yfn] << '\n';
    return 0;
}
