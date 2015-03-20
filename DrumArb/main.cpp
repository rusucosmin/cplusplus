// Fucking brute
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

string file = "drumarb";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, Q, Deep[MAXN], Level[MAXN << 1], Euler[MAXN << 1], K, RMQ[20][MAXN << 1], First[MAXN], Log[MAXN << 1], Last[MAXN];
Graph G;

void DFs(const int &Node, const int &Father, const int &actLevel) {
    First[Node] = ++ K;
    Euler[K] = Node;
    Level[K] = actLevel;
    Deep[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it) {
        if(*it == Father)
            continue;
        DFs(*it, Node, actLevel + 1);
        Euler[++K] = Node;
        Level[K] = actLevel;
    }
    Last[Node] = K;
}

inline void BuildLog() {
    for(int i = 2 ; i <= K ; ++ i)
        Log[i] = Log[i >> 1] + 1;
}

inline void BuildRMQ() {
    for(int i = 1 ; i <= K ; ++ i)
        RMQ[0][i] = i;
    for(int i = 1 ; (1 << i) <= K ; ++ i) {
        for(int j = 1 ; j + (1 << i) <= K ; ++ j) {
            if(Level[RMQ[i-1][j]] < Level[RMQ[i-1][j + (1 << (i-1))]])
                RMQ[i][j] = RMQ[i-1][j];
            else RMQ[i][j] = RMQ[i-1][j + (1 << (i - 1))];
        }
    }
}

inline int LCA(const int &a, const int &b) {
    int A = First[a];
    int B = First[b];
    if(A > B)
        swap(A, B);
    int diff = B - A + 1;
    int lg = Log[diff];
    int Ans = RMQ[lg][A];
    int sh = diff - (1 << lg);
    if(Level[Ans] > Level[RMQ[lg][A + sh]])
        Ans = RMQ[lg][A + sh];
    return Euler[Ans];
}

int main() {
    cin >> N >> Q;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0, 1);
    BuildLog();
    BuildRMQ();
    ifstream get("test.ok");

    for(int q = 1 ; q <= Q ; ++ q) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if(First[a] > First[b])
            swap(a, b);
        if(First[c] > First[d])
            swap(c, d);
        int lca_chain_1 = LCA(a, b);
        int lca_chain_2 = LCA(c, d);
        int Highest = max(Deep[lca_chain_1], Deep[lca_chain_2]);
        bool ok = false;
        int Ans = 0;

        int actLca = LCA(a, c);
        if(Deep[actLca] - Highest >= 0)
            Ans += max(0, Deep[actLca] - Highest), ok = true;

        actLca = LCA(a, d);
        if(Deep[actLca] - Highest >= 0)
            Ans += max(0, Deep[actLca] - Highest), ok = true;

        actLca = LCA(b, c);
        if(Deep[actLca] - Highest >= 0)
            Ans += max(0, Deep[actLca] - Highest), ok = true;

        actLca = LCA(b, d);
        if(Deep[actLca] - Highest >= 0)
            Ans += max(0, Deep[actLca] - Highest), ok = true;
        int myAns;
        get >> myAns;
        if(ok)
            Ans ++;
        cout << Ans << '\n';
    }
    cin.close();
    cout.close();
    return 0;
}
