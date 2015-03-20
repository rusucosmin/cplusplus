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

const char infile[] = "fof.in";
const char outfile[] = "fof.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, referenceplayer;
int nr[MAXN], ind[MAXN];
Graph G;
bitset <MAXN> Used;

struct classComp {
    inline bool operator () (const int &a, const int &b) const {
        return nr[a] > nr[b] || (nr[a] == nr[b] && a < b);
    }
};

void BFs(int Node) {
    queue <int> Q;
    Used.reset();
    Used[Node] = 1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        Q.push(*it);
        Used[*it] = 1;
    }
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it])
                ++ nr[*it];
    }
    for(int i = 1 ; i <= N ; ++ i)
        ind[i] = i;
    sort(ind + 1, ind + N + 1, classComp());
    for(int i = 1 ; i <= N ; ++ i) {
        if(nr[ind[i]])
            fout << ind[i] << ' ';
        nr[ind[i]] = 0;
    }
    fout << '\n';
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        BFs(i);
    fin.close();
    fout.close();
    return 0;
}
