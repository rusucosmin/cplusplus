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

string file = "arborest";

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

vector <int> d(MAXN, oo);
vector <int> Nodes;
int N, K, Father[MAXN], maxdeep;
Graph G;
queue <int> Q;
bitset<MAXN> Used;

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return d[a] > d[b];
    }
};

inline void BFs(int Node) {
    for(Q.push(Node) , d[Node] = 0 ; !Q.empty() ; Q.pop() , Node = Q.front() )
        for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
            if(d[*it] > d[Node] + 1)
                d[*it] = d[Node] + 1,
                maxdeep = max(maxdeep, d[*it]),
                Q.push(*it);
}

inline void DFs(int Node) {
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFs(*it);
}

inline int Look(int deep) {
    Used.reset();
    int ret = 0;
    for(int i = 0 ; i < N ; ++ i) {
        int Node = Nodes[i];
        if(Used[Node])
            continue;
        if(d[Node] >= deep) {
            int Dad = Father[Node];
            for(int j = 1 ; j <= deep - 2 ; ++ j)
                Dad = Father[Dad];
            if(!Used[Dad])
                ++ ret , DFs(Dad);
        }
    }
    return ret;
}

inline void Binary_Search() {
    int li = 0, ls = maxdeep;
    int mij;
    int Ans = oo;
    while(li <= ls) {
        mij = ((li + ls) / 2);
        int nr = Look(mij);
        if(nr > K)
            li = mij + 1;
        else {
            ls = mij - 1;
            if(nr == K) {
                Ans = mij;
            }
        }
    }
    cout << Ans << '\n';
}

int main() {
    cin >> N >> K;
    Nodes.push_back(1);
    for(int i = 2 ; i <= N ; ++ i)
        cin >> Father[i] , G[Father[i]].push_back(i), Nodes.push_back(i);
    BFs(1);
    random_shuffle(Nodes.begin(), Nodes.end());
    sort(Nodes.begin(), Nodes.end(), ClassComp());
    Binary_Search();
    cin.close();
    cout.close();
    return 0;
}
