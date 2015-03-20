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

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, Q, depth[MAXN], lowLink[MAXN];
stack<pair<int, int> > stk;
vector <set<int> > BCC;
vector <int> where[MAXN];
int comp;
Graph G;

inline void cache_bc(int x, int y) {
    int Tx, Ty;
    set<int> act
    ++ comp;
    do {
        Tx = stk.top().first;
        Ty = stk.top().second;
        act.insert(Tx);
        act.insert(Ty);
        where[Tx].push_back(comp);
        where[Ty].push_back(comp);
    }while(Tx != x || Ty != y);
    BCC.push_back(act);
}

inline void DFs(int Node, int Father, int actLevel) {
    depth[Node] = lowLink[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        if(!depth[*it]) {
            stk.push(make_pair(Node, *it));
            Dfs(*it, Node, actLevel + 1);
            lowLink[Node] = min(lowLink[Node], lowLink[*it]);
            if(lowLink[*it] >= depth[Node])
                cache_bc(Node, *it);
        }
        else lowLink[Node] = min(lowLink[Node], depth[*it]);
    }
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!depth[i])
            DFs(i, i, 1);
    cin >> Q;
    for(int i = 1 ; i <= Q ; ++ i) {
        int op, a, b, c, d;
        cin >> op;
        switch(op) {
            case 1:
                cin >> a >> b >> c >> d;
                break;
            case 2:
                cin >> a >> b >> c >> d;
                break;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
