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

const char infile[] = "colorare.in";
const char outfile[] = "colorare.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 16;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
Graph G;
int minIndependSet;
int minColors;
int nrColors, colors;
int color[MAXN];
int fact[MAXN];
bitset <MAXN> Used;

void Back(int K) {
    if(K == N + 1) {
        if(minColors > colors) {
            minColors = colors;
            nrColors = 1;
        }
        else {
            if(minColors == colors) {
//                for(int i = 1 ; i <= N ; ++ i)
 //                   if(color[i] > colors)
  //                      return;
                ++ nrColors;
            }
        }
        return ;
    }
    for(int i = 1 ; i <= minColors ; ++ i) {
        bool color_ok = true;
        for(It it = G[K].begin(), fin = G[K].end(); it != fin && color_ok ; ++ it)
            if(color[*it] == i)
                color_ok = false;
        if(!color_ok)
            continue;
        color[K] = i;
        bool first_color = false;
        if(!Used[i]) {
            first_color = true;
            Used[i] = true;
            ++ colors;
        }
        Back(K + 1);
        if(first_color) {
            Used[i] = false;
            -- colors;
        }
        color[K] = 0;
    }
}

int main() {
    fin >> N >> M;
    minColors = N;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    Back(1);
    fout << minColors << ' ' << nrColors  << '\n';
    fin.close();
    fout.close();
    return 0;
}
