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
#include <stack>

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

int N, M, depth[MAXN], lowLink[MAXN], Father[MAXN];
Graph G, E;
stack <pair<int, int> > st;
set <pair<int, int> > criticalEdges;
bitset <MAXN> Used;

inline int Find(int x) {
    if(Father[x] != x)
        Father[x] = Find(Father[x]);
    return Father[x];
}

inline void Unite(int x, int y) {
    int Tx = Find(x);
    int Ty = Find(y);
    if(Tx == Ty)
        return;
    if(Tx > Ty)
        swap(Tx, Ty);
    Father[Tx] = Father[Ty];
}

inline void ExtractBiconnectedComponent(int x, int y) {
    int Tx, Ty;
    set<int> S;
    do {
        Tx = st.top().first;
        Ty = st.top().second;
        S.insert(Tx);
        S.insert(Ty);
        st.pop();
    } while(Tx != x || Ty != y);
    if(S.size() > 2)
        for(set<int> :: iterator it = S.begin(), fin = S.end(); it != fin ; ++ it)
            Unite(*it, *S.begin());
}

inline void DFs(int Node, int father, int actLevel) {
    depth[Node] = lowLink[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == father)
            continue;
        if(!depth[*it]) {
            st.push(make_pair(Node, *it));
            DFs(*it, Node, actLevel + 1);
            lowLink[Node] = min(lowLink[Node], lowLink[*it]);
            if(lowLink[*it] >= depth[Node]) {
                if(lowLink[*it] > depth[Node])
                    criticalEdges.insert(make_pair(Node, *it));
                ExtractBiconnectedComponent(Node, *it);
            }
        } else lowLink[Node] = min(lowLink[Node], depth[*it]);
    }
}

inline void DFs(int Node, vector <int> &Ans) {
    Used[Node] = 1;
    bool leaf = true;
    for(It it = E[Node].begin(), fin = E[Node].end(); it != fin ; ++ it)
        if(!Used[*it]) {
            DFs(*it, Ans);
            leaf = false;
        }
    if(leaf)
        Ans.push_back(Node);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N >> M;
    if(N == 2) {
        cout << "-1\n";
        return 0;
    }
    for(int i = 1 ; i <= N ; ++ i)
        Father[i] = i;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0, 1);
    for(set<pair<int, int> > :: iterator it = criticalEdges.begin(), fin = criticalEdges.end(); it != fin ; ++ it) {
        int x = Find(it->first);
        int y = Find(it->second);
        E[x].push_back(y);
        E[y].push_back(x);
    }
    vector <int> Ans;
    for(int i = 1 ; i <= N ; ++ i) {
        if(E[i].size() == 1) {
            Ans.push_back(i);
        }
        else if(E[i].size() > 1) {
            Ans.clear();
            DFs(i, Ans);
            break;
        }
    }
    if(Ans.size() & 1)
        Ans.push_back(Ans.back());
    int sz = Ans.size() / 2;
    cout << sz << '\n';
    for(int i = 0 ; i < sz ; ++ i)
        cout << Ans[i] << ' ' << Ans[sz + i] << '\n';
    fin.close();
    fout.close();
    return 0;
}
