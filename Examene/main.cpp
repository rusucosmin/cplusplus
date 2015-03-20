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

string file = "examene";

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

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

int N, M, P, Dad[MAXN], Level[MAXN], StartCycle;
bool a[305][305];
Graph G, Gt;
bitset<MAXN> Useful, Used, inCycle;

inline void DFs(int Node) {
    Useful[Node] = true;
    for(It it = Gt[Node].begin(), fin = Gt[Node].end() ; it != fin ; ++ it)
        if(!Useful[*it])
            DFs(*it);
}

inline void DFs2(int Node) {
    if(inCycle[StartCycle])
        return;
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
        if(*it == StartCycle)
            inCycle[StartCycle] = true;
        else if(!Used[*it])
            DFs2(*it);

}

inline void findCycles() {
    /// finding cycles o(n * (n+m) ) - worst case
    for(int i = 1 ; i <= N ; ++ i)
        if(!inCycle[i]) {
            Used.reset();
            StartCycle = i;
            DFs2(i);
        }
    /*
    finding Cycles o(n^3)
    for(int k = 1 ;  k <= N ; ++ k)
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= N ; ++ j)
                if(a[i][k] && a[k][j])
                    a[i][j] = true;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            if(a[i][j] && a[j][i])
                inCycle[i] = true, inCycle[j] = true;
    */
}

int main() {
    cin >> N >> M >> P;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        a[x][y] = 1;
        Gt[y].push_back(x);
    }
    for(int i = 1 ; i <= P ; ++ i) {
        int x;
        cin >> x;
        if(!Useful[x])
            DFs(x);
    }
    findCycles();
    if(Useful.count() == N)
        cout << "0\n";
    else
        for(int i = 1 ; i <= N ; ++ i)
            if(!Useful[i])
                cout << i << ' ';
    cout << '\n';
    if(inCycle.count() == 0)
        cout << "0\n";
    else
        for(int i = 1 ; i <= N ; ++ i)
            if(inCycle[i])
                cout << i << ' ';
    cin.close();
    cout.close();
    return 0;
}
