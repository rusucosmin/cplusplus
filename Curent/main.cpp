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

string file = "curent";

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

struct qry {
    bool op;
    int a, b, c;
    qry(bool _op, int _a, int _b, int _c) {
        op = _op;
        a = _a;
        b = _b;
        c = _c;
    }
    void write() {
        cout << op << ' ' << a << ' ' << b << ' ' << c << '\n';
    }
};

struct node {
    int sum, ars;
};

struct ClassComp {
    inline bool operator () (const qry &a, const qry &b) const {
        return a.a < b.a;
    }
};

int N, M, Father[MAXN], Euler[MAXN], First[MAXN], Last[MAXN], K, U, Q;
node aint[MAXN << 2];
Graph G;
vector <qry> query;

/// <aint>
inline int leftSon(int actNode) {
    return (actNode << 1);
}
inline int rightSon(int actNode) {
    return (actNode << 1) + 1;
}
void Build(int Node, int st, int dr) {
    if(st == dr) {
        aint[Node].sum = 1;
        return ;
    }
    int mid = ((st + dr) >> 1);
    Build(leftSon(Node), st, mid);
    Build(rightSon(Node), mid+1, dr);
    aint[Node].sum = aint[leftSon(Node)].sum + aint[rightSon(Node)].sum;
}
void Update(int Node, int st, int dr, int a, int b, bool op) {
    if(a <= st && dr <= b) {
        if(!op) {
            ++ aint[Node].ars;
            aint[Node].sum = 0;
        }
        else {
            -- aint[Node].ars;
            if(!aint[Node].ars && st == dr) {
                aint[Node].sum = 1;
                return;
            }
        }
        if(!aint[Node].ars)
            aint[Node].sum = aint[leftSon(Node)].sum + aint[rightSon(Node)].sum;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(a <= mid)
        Update(leftSon(Node), st, mid, a, b, op);
    if(mid < b)
        Update(rightSon(Node), mid+1, dr, a, b, op);
    if(!aint[Node].ars)
        aint[Node].sum = aint[leftSon(Node)].sum + aint[rightSon(Node)].sum;
}
/// </aint>

inline void Read() {
    cin >> N;
    for(int i = 2 ; i <= N ; ++ i) {
        cin >> Father[i];
        G[Father[i]].push_back(i);
    }
    cin >> U;
    for(int i = 1 ; i <= U ; ++ i) {
        int a, b, c;
        cin >> a >> b >> c;
        query.push_back(qry(1, a, b, c));
    }
    cin >> Q;
    for(int i = 1 ; i <= Q ; ++ i) {
        int x;
        cin >> x;
        query.push_back(qry(0, x, 0, 0));
    }
    sort(query.begin(), query.end(), ClassComp());
}

inline void Solve() {
    Build(1, 1, N);
    for(int i = 0 ; i < query.size() ; ++ i) {
        qry act = query[i];
        if(!act.op)
            cout << aint[1].sum << '\n';
        else
            Update(1, 1, N, First[act.b], Last[act.b], act.c);
    }
}

void DFs(int Node) {
    Euler[++K] = Node;
    First[Node] = Last[Node] = K;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        DFs(*it);
    }
    Last[Node] = K;
}

int main() {
    Read();
    DFs(1);
    Solve();
    cin.close();
    cout.close();
    return 0;
}
