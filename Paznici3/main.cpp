#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <list>
#include <iomanip>

using namespace std;

string file = "paznici3";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct paznic {
    int a, b, z;
    paznic() {
        a = b = z = 0;
    }
    paznic(int _a, int _b, int _z) {
        a = _a;
        b = _b;
        z = _z;
    }
};

struct ClassComp {
    inline bool operator () (const paznic &a, const paznic &b) const {
        return a.z < b.z;
    }
};

int N, M, K, eulerLevel[MAXN << 1], RMQ[25][MAXN << 1], Euler[MAXN], First[MAXN], Lg[MAXN], Father[MAXN], dp[MAXN];
Graph G;
paznic P[MAXN];
set< paznic, ClassComp > LCA[MAXN];

void DFs(int Node, int Dad, int actLevel) {
    Father[Node] = Dad;
    Euler[ ++ K ] = Node;
    eulerLevel[K] = actLevel;
    First[Node] = K;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Dad)
            continue;
        DFs(*it, Node, actLevel + 1);
        Euler[ ++ K ] = Node;
        eulerLevel[K] = actLevel;
    }
}

inline void BuildRMQ() {
    for(int i = 1 ; i <= K ; ++ i)
        RMQ[0][i] = i;
    for(int i = 1 ; ( 1 << i ) <= K ; ++ i)
        for(int j = 1 ; j <= K - ( 1 << i ) + 1 ; ++ j) {
            int l = (1 << (i - 1));
            RMQ[i][j] = RMQ[i-1][j];
            if(eulerLevel[RMQ[i][j]] > eulerLevel[RMQ[i-1][j+l]])
                RMQ[i][j] = RMQ[i-1][j+l];
        }
}

inline void BuildLog() {
    for(int i = 2 ; i <= K ; ++ i)
        Lg[i] = Lg[i >> 1] + 1;
}

inline int lca(int a, int b) {
    int A = First[a];
    int B = First[b];
    if(A > B)
        swap(A, B);
    int diff = B - A + 1;
    int logg = Lg[diff];
    int Ans = RMQ[logg][A];
    int sh = diff - (1 << logg);
    if(eulerLevel[Ans] > eulerLevel[RMQ[logg][A + sh]])
        Ans = RMQ[logg][A + sh];
    return Euler[Ans];
}

int buildMinimum(const paznic &p, int ancestor) {
    int A = p.a;
    int B = p.b;
    int Z = p.z;
    //cout << A << " " << B << " " << ancestor << "\n";
    int actNode;
    int Ret = Z;
    int last = 0;
    for(actNode = A ; actNode != ancestor ; last = actNode, actNode = Father[actNode])
        for(It it = G[actNode].begin(), fin = G[actNode].end(); it != fin ; ++ it) {
            if(*it == Father[actNode] || *it == last)
                continue;
            if(dp[*it] == oo)
                return oo;
    //        cout << *it << '\n';
            Ret += dp[*it];
        }
    int last1 = 0;
    for(actNode = B ; actNode != ancestor ; last1 = actNode, actNode = Father[actNode])
        for(It it = G[actNode].begin(), fin = G[actNode].end(); it != fin ; ++ it) {
            if(*it == Father[actNode] || *it == last1)
                continue;
            if(dp[*it] == oo)
                return oo;
   //         cout << *it << '\n';
            Ret += dp[*it];
        }

    for(It it = G[ancestor].begin(), fin = G[ancestor].end(); it != fin ; ++ it) {
            if(*it == Father[actNode] || *it == last1 || *it == last)
                continue;
            if(dp[*it] == oo)
                return oo;
    //        cout << *it << '\n';
            Ret += dp[*it];
        }
    return Ret;
}

void DFs(int Node, int Dad) {
    bool leaf = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Dad)
            continue;
        leaf = false;
        DFs(*it, Node);
    }
    if(leaf) {
        if(LCA[Node].size())
            dp[Node] = LCA[Node].begin()->z;
        else dp[Node] = oo;
        return;
    }
    int act = oo;
    for(set<paznic> :: iterator it = LCA[Node].begin(), fin = LCA[Node].end() ; it != fin ; ++ it) {
        act = min(act, buildMinimum(*it, Node));
    }
    dp[Node] = act;
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 1, 1);
    BuildRMQ();
    BuildLog();
    for(int i = 1 ; i <= M ; ++ i) {
        cin >> P[i].z >> P[i].a >> P[i].b;
    //    cout << " LCA : " << lca(P[i].a, P[i].b) << '\n';
        LCA[lca(P[i].a, P[i].b)].insert(P[i]);
    }
    DFs(1, 1);
    //for(int i = 1 ; i <= N ; ++ i)
        cout << dp[1] << '\n';
    cin.close();
    cout.close();
    return 0;
}
