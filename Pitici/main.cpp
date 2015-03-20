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

string file = "pitici";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 1025;
const int oo = 0x3f3f3f3f;

typedef pair<int, int> edge;
typedef vector<edge> Graph[MAXN];
typedef vector<edge> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const edge &a, const edge &b) const {
        return a.second > b.second;
    }
};

int N, M, K;
vector<int> tSort, deg(MAXN), dmin(MAXN, oo);
queue<int> Q;
Graph G;
///dmin[i] = distanta minima de la nodul i la nodul N

priority_queue< edge, vector<edge>, greater_equal<edge> > H;

int main() {
    cin >> N >> M >> K;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        G[x].push_back(make_pair(y, z));
        ++ deg[y];
    }
    for(Q.push(1) ; !Q.empty() ; Q.pop()) {
        int Node = Q.front();
        tSort.push_back(Node);
        for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it) {
            -- deg[it->first];
            if(!deg[it->first])
                Q.push(it->first);
        }
    }
    dmin[N] = 0;
    for(int i = N - 1; i >= 0 ; -- i) {
        int Node = tSort[i];
        for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
            dmin[Node] = min(dmin[Node], dmin[it->first] + it->second);
    }
    int nRoads = 0;
    for(H.push(make_pair(dmin[1], 1)) ; nRoads < K ;) {
        int Node = H.top().second;
        int dist = H.top().first;
        H.pop();
        int backdistance = dist - dmin[Node];
        if(Node == N) {
            cout << dist << ' ';
            ++ nRoads;
            continue;
        }
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            H.push(make_pair(backdistance + it->second + dmin[it->first], it->first));
        }
    }
    cin.close();
    cout.close();
    return 0;
}
