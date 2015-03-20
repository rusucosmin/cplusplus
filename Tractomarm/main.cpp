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

const char infile[] = "tractomarm.in";
const char outfile[] = "tractomarm.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 250005;
const int MAXQ = 400005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Query {
    int father;
    bool parity;
    int ind;
};

Graph G;
vector <Query> T[MAXN];
bitset <MAXN> Used;
int level[MAXN], subArb[MAXN];
long long st[MAXN];
int top, N, Q;
long long Sum, Ans[MAXQ];

void DFs(int Node, int actLevel) {
    Used[Node] = true;
    level[Node] = actLevel;
    subArb[Node] = 1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it]) {
            DFs(*it, actLevel + 1);
            subArb[Node] += subArb[*it];
        }
    Sum += level[Node];
}

void solveQueries(int Node, int Father) {
    Used[Node] = true;
    st[++ top] = st[top - 1] + subArb[Node];
    for(vector <Query> :: iterator it = T[Node].begin(), fin = T[Node].end(); it != fin ; ++ it) {
        Ans[it->ind] = 2 * (st[top] - st[top - it->father]);
        if(it->parity)
            Ans[it->ind] += st[top - it->father] - st[top - it->father - 1];
    }
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
        if(!Used[*it])
            solveQueries(*it, Node);
    -- top;
}

int main() {
    fin >> N;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0);
    fin >> Q;
    for(int i = 1 ; i <= Q ; ++ i) {
        Query qu;
        int x, y;
        fin >> x >> y;
        if(level[x] + 1 < level[y])
            swap(x, y);
        if(level[y] + 1 < level[x]) {
            int aux = level[x] - level[y] - 1;
            qu.parity = aux % 2;
            qu.father = aux / 2;
            qu.ind = i;
            T[x].push_back(qu);
        }
    }
    Used.reset();
    solveQueries(1, 0);
    for(int i = 1 ; i <= Q; ++ i)
        fout << Sum - Ans[i] << '\n';
    fin.close();
    fout.close();
    return 0;
}
