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

#define mp make_pair
#define x first
#define y second

using namespace std;

const char infile[] = "trenuri2.in";
const char outfile[] = "trenuri2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

typedef pair<int, int> per;
typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

Graph G;
int First[MAXN], RMQ[20][MAXN << 1], Level[MAXN << 1], Log[MAXN << 1], Euler[MAXN << 1], H[MAXN];
int in[MAXN], out[MAXN], K, P, N, Q;
vector < pair<int, pair<int, int> > > actions;
int a[MAXN], b[MAXN], d[MAXN], v[MAXN], x[MAXN], y[MAXN], sp[MAXN];
double aibViteza[MAXN << 1], Ans[MAXN];
int aibDistanta[MAXN << 1];

void DFs(int Node, int Father, int actLevel) {
    in[Node] = ++ P;
    H[Node] = actLevel;
    First[Node] = ++ K;
    Level[K] = actLevel;
    Euler[K] = Node;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        DFs(*it, Node, actLevel + 1);
        Euler[++ K] = Node;
        Level[K] = actLevel;
    }
    out[Node] = ++ P;
}

inline void BuildLog() {
    Log[1] = 0;
    for(int i = 2 ; i <= K ; ++ i)
        Log[i] = Log[i >> 1] + 1;
}

inline void BuildRMQ() {
    for(int i = 1 ; i <= K ; ++ i)
        RMQ[0][i] = i;
    for(int i = 1 ; (1 << i) <= K ; ++ i) {
        for(int j = 1 ; j + (1 << i) - 1 <= K ; ++ j) {
            int l = (1 << (i - 1));
            RMQ[i][j] = RMQ[i - 1][j];
            if(Level[RMQ[i][j]] > Level[RMQ[i - 1][j + l]])
                RMQ[i][j] = RMQ[i - 1][j + l];
        }
    }
}

inline int LCA(int x, int y) {
    x = First[x];
    y = First[y];
    if(x > y)
        swap(x, y);
    int diff = (y - x + 1);
    int lg = Log[diff];
    int Ans = RMQ[lg][x];
    if(Level[Ans] > Level[RMQ[lg][y - (1 << lg) + 1]])
        Ans = RMQ[lg][y - (1 << lg) + 1];
    return Euler[Ans];
}

inline int lsb(int x) {
    return x & (-x);
}

void Update(int pos, int val1, double val2) {
    for(int i = pos ; i <= K ; i += lsb(i)) {
        aibDistanta[i] += val1;
        aibViteza[i] += val2;
    }
}

inline double Query(int pos, int viteza) {
    double sum1 = 0, sum2 = 0;
    for(int i = pos ; i > 0 ; i -= lsb(i)) {
        sum1 += aibDistanta[i];
        sum2 += aibViteza[i];
    }
    return sum2 + 1.0 * sum1 / (double)viteza;
}

int main() {
    fin >> N >> Q;
    for(int i = 1 ; i != N ; ++ i) {
        fin >> a[i] >> b[i] >> d[i] >> v[i];
        G[a[i]].push_back(b[i]);
        G[b[i]].push_back(a[i]);
        actions.push_back(make_pair(v[i], make_pair(0, i)));
    }
    for(int i = 1 ; i <= Q ; ++ i) {
        fin >> x[i] >> y[i] >> sp[i];
        actions.push_back(make_pair(sp[i], make_pair(1, i)));
    }
    sort(actions.begin(), actions.end());
    DFs(1, 0, 1);
    BuildLog();
    BuildRMQ();
    for(int i = 1 ; i != N ; ++ i) {
        if(H[a[i]] < H[b[i]])
            swap(a[i], b[i]);
        Update(in[a[i]], d[i], 0);
        Update(out[a[i]], -d[i], 0);
    }
    for(vector<pair<int, pair<int, int> > > :: iterator it = actions.begin(), fin = actions.end(); it != fin ; ++ it) {
        if(it -> second.first == 0) {
            int ind = it->second.second;
            Update(in[a[ind]], -d[ind], 1.0 * d[ind] / (double)v[ind]);
            Update(out[a[ind]], d[ind], -1.0 * d[ind] / (double)v[ind]);
        } else {
            int ind = it->second.second;
            int lca = LCA(x[ind], y[ind]);
            Ans[ind] = Query(in[x[ind]], sp[ind]) + Query(in[y[ind]], sp[ind]) - 2.0 * (Query(in[lca], sp[ind]));
        }
    }
    for(int i = 1 ; i <= Q ; ++ i)
        fout << fixed << setprecision(4) << Ans[i] << '\n';
    fin.close();
    fout.close();
    return 0;
}
