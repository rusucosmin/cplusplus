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

const char infile[] = "kdist.in";
const char outfile[] = "kdist.out";

ofstream fout(outfile);

const int MAXN = 200005;
const int oo = 0x3f3f3f3f;

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

Graph G, V;
int N, K, H, Euler[MAXN << 2], Level[MAXN << 2], RMQ[25][MAXN << 2], First[MAXN], depth[MAXN];
int Father[MAXN], s[MAXN], Log[MAXN << 2];
int color[MAXN];

struct Entry {
    int lca, x, y;
    Entry(int _lca, int _x, int _y) {
        lca = _lca;
        x = _x;
        y = _y;
    }
};

struct classComp {
    inline bool operator () (const Entry &a, const Entry &b) const {
        return depth[a.lca] > depth[b.lca];
    }
};

inline void DFs(int Node, int Father, int actLevel) {
    V[color[Node]].push_back(Node);
    First[Node] = ++ H;
    Euler[H] = Node;
    Level[H] = actLevel;
    depth[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        DFs(*it, Node, actLevel + 1);
        Euler[++ H] = Node;
        Level[H] = actLevel;
    }
}

inline void buildRMQ() {
    for(int i = 2 ; i <= H ; ++ i)
        Log[i] = Log[i >> 1] + 1;
    for(int i = 1 ; i <= H ; ++ i)
        RMQ[0][i] = i;
    for(int i = 1 ; (1 << i) <= H ; ++ i)
        for(int j = 1 ; j + (1 << i) - 1 <= H ; ++ j) {
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
    int ans = RMQ[lg][x];
    if(Level[ans] > Level[RMQ[lg][y - (1 << lg) + 1]])
        ans = RMQ[lg][y - (1 << lg) + 1];
    return Euler[ans];
}

inline int Find(int x) {
    if(Father[x] != x)
        Father[x] = Find(Father[x]);
    return Father[x];
}

int main() {
    freopen(infile, "r", stdin);
    getInt(N);
    getInt(K);
    for(int i = 1 ; i < N ; ++ i) {
        int x, y;
        getInt(x);
        getInt(y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        getInt(color[i]);
    DFs(1, 0, 1);
    buildRMQ();
    for(int i = 1 ; i <= N ; ++ i) {
        s[i] = 1;
        Father[i] = i;
    }
    for(int col = 1 ; col <= K ; ++ col) {
        cerr << col << '\n';
        if(V[col].size() <= 1) {
            fout << "0\n";
            continue;
        }
        vector <Entry> LCAs;
        long long Ans = 0;
        for(int i = 0 ; i < V[col].size() ; ++ i) {
            Ans += 1LL * (V[col].size() - 1) * depth[V[col][i]];
            if(i == 0)
                continue;
            LCAs.push_back(Entry(LCA(V[col][i - 1], V[col][i]), V[col][i - 1], V[col][i]));
        }
        sort(LCAs.begin(), LCAs.end(), classComp());
        for(vector <Entry> :: iterator it = LCAs.begin(), fin = LCAs.end(); it != fin ; ++ it) {
            int lca = it->lca;
            int x = it->x;
            int y = it->y;
            int Tx = Find(x);
            int Ty = Find(y);
            Ans -= 2LL * depth[lca] * s[Tx] * s[Ty];
            Father[Tx] = Ty;
            s[Ty] += s[Tx];
            s[Tx] = 0;
        }
        fout << Ans << '\n';
    }
    fout.close();
    return 0;
}
