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

string file = "catun";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 36005;
const int oo = 0x3f3f3f3f;

typedef pair<int, int > edge;
typedef vector<edge> Graph[MAXN];
typedef vector<edge> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

int N, M, K;
bitset<MAXN> Catun;
vector<int> d(MAXN, oo), C(MAXN);
queue<int> Q;
Graph G;

inline void Dijkstra() {
    for( ; !Q.empty() ; Q.pop() ) {
        int Node = Q.front();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(d[it->first] > d[Node] + it->second || (d[it->first] == d[Node] + it->second && C[it->first] > C[Node])) {
                C[it->first] = C[Node];
                d[it->first] = d[Node] + it->second;
                Q.push(it->first);
            }
    }
}

int main() {
    cin >> N >> M >> K;
    for(int i = 1 ; i <= K ; ++ i) {
        int x;
        cin >> x;
        Catun[x] = true;
        C[x] = x;
        d[x] = 0;
        Q.push(x);
    }
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    Dijkstra();
    for(int i = 1 ; i <= N ; ++ i)
        if(C[i] == i)
            cout << "0 ";
        else cout << C[i] << ' ';
    cin.close();
    cout.close();
    return 0;
}
