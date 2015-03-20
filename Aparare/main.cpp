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

string file = "aparare";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;

template<class T>
class edgeHeap {
private:
    priority_queue< T > Heap;
    bitset<MAXN> Used;
public:
    void Add(int Node) {
        Used[Node] = true;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[it->first]) {
                Heap.push(make_pair(it->second, it->first));
            }
    }
    T getTop() {
        return Heap.top();
    }
    void Clear() {
        while(!Heap.empty())
            Heap.pop();
        Used.reset();
    }
    void Erase() {
        Heap.pop();
    }
};

vector< pair<int, pair<int, int> > > Edge;
int N, M, Father[MAXN];
long long totalCost, max4EdgesCost;
edgeHeap <pair<int, int> > Q;

int Find(int Node) {
    if(Father[Node] != Node)
        Father[Node] = Find(Father[Node]);
    return Father[Node];
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        Edge.push_back(make_pair(z, make_pair(x, y)));
    }
    for(int i = 1 ; i <= N ; ++ i)
        Father[i] = i;
    sort(Edge.begin(), Edge.end());
    for(int i = 0 ; i < M ; ++ i) {
        int cost = Edge[i].first;
        int x = Edge[i].second.first;
        int y = Edge[i].second.second;
        int Tx = Find(x);
        int Ty = Find(y);
        if(Tx != Ty) {
            /// unite
            Father[Tx] = Ty;
            totalCost += cost;
            G[x].push_back(make_pair(y, cost));
            G[y].push_back(make_pair(x, cost));
        }
    }
    /**
     *  Strategia e urmatoarea : aleg un nod arbitrar, i, bag vecinii sai intr-un minHeap, iar apoi ma extind insprea alte 4
     *  noduri
     */
    for(int i = 1 ; i <= N ; ++ i) {
        int act4EdgesCost = 0;
        Q.Clear();
        Q.Add(i);
        for(int j = 1 ; j < 5 ; ++ j) {
            pair<int, int> Top = Q.getTop();
            Q.Erase();
            Q.Add(Top.second);
            act4EdgesCost += Top.first;
        }
        max4EdgesCost = max(max4EdgesCost, act4EdgesCost);
    }
    cout << totalCost << ' ' << totalCost - max4EdgesCost << '\n';
    cin.close();
    cout.close();
    return 0;
}
