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

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef set<int> Graph[MAXN];
typedef set<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, M, N, start, Ans;

set<int> G[7 * 7 + 5];

#define fin cin
#define fout cout

void DFs(const int &Node, const int &Father) {
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it != Father) {
            DFs(*it, Node);
            ++ Ans;
        }
    }
    ++ Ans;
}

int main() {
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        fin >> start >> N >> M;
        Ans = 0;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            fin >> x >> y;
            G[x].insert(y);
            G[y].insert(x);
        }
        DFs(start, -1);
        fout << Ans - 1 << '\n';
        for(int i = 0 ; i <= N ; ++ i)
            set<int>().swap(G[i]);
    }
    return 0;
}
