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

string file = "arb2";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

struct mp {
    int x, d, c;
    mp(int _x, int _d, int _c): x(_x), d(_d), c(_c) {}
};

typedef vector<mp> Graph[MAXN];
typedef vector<mp> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

int N;
long long dmax[MAXN], cmin[MAXN], Ans;
Graph G;

inline void DFs(int Node, int Father) {
    int sons = 0;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it) {
        if(it->x == Father)
            continue;
        ++ sons;
        DFs(it->x, Node);
        dmax[Node] = max(dmax[Node], (long long) dmax[it->x] + (long long) it->d);
        cmin[it->x] = min(cmin[it->x], (long long) it->c);
        cmin[Node] += (long long)cmin[it->x];
    }
    if(!sons)
        cmin[Node] = oo;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it) {
        if(it->x == Father)
            continue;
        Ans += (long long)cmin[it->x] * (long long)(dmax[Node] - (dmax[it->x] + it->d));
    }
}

int main() {
    cin >> N;
    for(int i = 1 ; i != N ; ++ i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        G[a].push_back(mp(b, c, d));
        G[b].push_back(mp(a, c, d));
    }
    DFs(1, 0);
    cout << Ans << '\n';
    cin.close();
    cout.close();
    return 0;
}
