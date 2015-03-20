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

const char infile[] = "posta3.in";
const char outfile[] = "posta3.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 3005;
const int oo = 0x3f3f3f3f;
const int MOD = 666013;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getInt(int &x) {
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9'))
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

Graph G, bipartite;
int N, X;
int depth[MAXN];
int match[MAXN], mate[MAXN], father[MAXN], value[MAXN];
bitset <MAXN> Used;

inline void DFs(int Node, int actLevel) {
    depth[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(depth[*it])
            continue;
        father[*it] = Node;
        DFs(*it, actLevel + 1);
    }
}

inline bool pairUp(int Node) {
    if(Used[Node])
        return 0;
    Used[Node] = 1;
    for(It it = bipartite[Node].begin(), fin = bipartite[Node].end();  it != fin ; ++ it)
        if(!mate[*it] || pairUp(mate[*it])) {
            match[Node] = *it;
            mate[*it] = Node;
            return 1;
        }
    return 0;
}

inline int getMaxMatching(Graph &G, int L, int R) {
    int maxMatching = 0;
    for(bool change = true ; change ; ) {
        change = false;
        Used.reset();
        for(int i = 1 ; i <= L ; ++ i)
            if(!match[i] && pairUp(i)) {
                change = 1;
                ++ maxMatching;
            }
    }
    return maxMatching;
}

int main() {
    freopen(infile, "r", stdin);
    getInt(N);
    getInt(X);
    for(int i = 1 ; i < N ; ++ i) {
        int x, y;
        getInt(x);
        getInt(y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        getInt(value[i]);
    DFs(1, 1);
    vector <int> a, b;
    while(X) {
        Used[X] = 1;
        a.push_back(X);
        X = father[X];
    }
    for(It it = a.begin(), fin = a.end(); it != fin ; ++ it) {
        for(It vec = G[*it].begin(), fvec = G[*it].end() ; vec != fvec ; ++ vec)
            if(!Used[*vec]) {
                Used[*vec] = 1;
                b.push_back(*vec);
            }
    }
    for(It i = a.begin() ; i != a.end() ; ++ i)
        for(It j = b.begin() ; j != b.end() ; ++ j)
            if(depth[*i] >= depth[*j] && value[*i] <= value[*j])
                bipartite[i - a.begin() + 1].push_back(j - b.begin() + 1);
    fout << getMaxMatching(bipartite, a.size(), b.size()) << '\n';
    fin.close();
    fout.close();
    return 0;
}
