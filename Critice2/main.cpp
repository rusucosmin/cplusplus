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

const char infile[] = "critice2.in";
const char outfile[] = "critice2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int N, M, E;
int Euler[MAXN << 2], Level[MAXN << 2], RMQ[25][MAXN << 2], K, First[MAXN], Log[MAXN << 2];
int lowLink[MAXN], depth[MAXN];
int newNode[MAXN], oldNode[MAXN], vertices;
bitset <MAXN> Used, isCritic;

void DFs(int Node, int Father, int actLevel) {
    Used[Node] = 1;
    newNode[Node] = ++ vertices;
    oldNode[newNode[Node]] = Node;
    Euler[ ++ K ] = newNode[Node];
    Level[K] = actLevel;
    First[newNode[Node]] = K;
    for(It it = G[Node].begin(), fin= G[Node].end(); it != fin ; ++ it) {
        if(!Used[*it]) {
            DFs(*it, Node, actLevel + 1);
            Euler[++ K] = newNode[Node];
            Level[K] = actLevel;
        }
    }
}

void getCriticalEdges(int Node, int Father, int actLevel) {
    int fatherEdges = 0;
    depth[Node] = lowLink[Node] = actLevel;
    Used[Node] = 1;
    bool critic = false;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father) {
            ++ fatherEdges;
            continue;
        }
        if(!Used[*it]) {
            getCriticalEdges(*it, Node, actLevel + 1);
            lowLink[Node] = min(lowLink[Node], lowLink[*it]);
        } else lowLink[Node] = min(lowLink[Node], depth[*it]);
    }
    if(lowLink[Node] > depth[Father] && fatherEdges <= 1)
        critic = true;
    isCritic[Node] = critic;
}

inline void buildRMQ() {
    for(int i = 2 ; i <= K ; ++ i)
        Log[i] = Log[i >> 1] + 1;
    for(int i = 1 ; i <= K ; ++ i)
        RMQ[0][i] = i;
    for(int i = 1 ; (1 << i) <= K ; ++ i)
        for(int j = 1 ; j + (1 << i) - 1 <= K ; ++ j) {
            int aux = (1 << (i - 1));
            RMQ[i][j] = RMQ[i - 1][j];
            if(Level[RMQ[i][j]] > Level[RMQ[i - 1][j + aux]])
                RMQ[i][j] = RMQ[i - 1][j + aux];
        }
}

inline int LCA(int x, int y) {
    x = First[x];
    y = First[y];
    if(x > y)
        swap(x, y);
    int lg = Log[y - x + 1];
    int Ans = RMQ[lg][x];
    if(Level[Ans] > Level[RMQ[lg][y - (1 << lg) + 1]])
        Ans = RMQ[lg][y - (1 << lg) + 1];
    return Euler[Ans];
}

double S[MAXN], R[MAXN], Ans;

inline void lastDFs(int Node) {
    Used[newNode[Node]] = 1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[newNode[*it]]) {
            lastDFs(*it);
            S[newNode[Node]] *= S[newNode[*it]];
        }
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        if(x == y)
            continue;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0, 1);
    buildRMQ();
    Used.reset();
    getCriticalEdges(1, 0, 1);
    fin >> E;
    for(int i = 0 ; i <= N ; ++ i)
        S[i] = 1;
    for(int i = 1 ; i <= E ; ++ i) {
        int x, y;
        double p, cp;
        fin >> x >> y >> p;
        if(x == y)
            continue;
        p = 1 - p; /// probabilitatea ca sa nu apara
        x = newNode[x];
        y = newNode[y];
        cp = p;
        int lca = LCA(x, y);
        if(lca == x)
            swap(x, y);
        if(lca == y) {
            S[lca] /= cp;
            S[x] *= cp;
            continue;
        }
        S[lca] /= cp;
        S[lca] /= cp;
        S[x] *= cp;
        S[y] *= cp;
    }
    Used.reset();
    lastDFs(1);
    for(int i = 2 ; i <= N ; ++ i)
        if(isCritic[oldNode[i]])
            Ans += S[i];
    fout << fixed << setprecision(6) << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
