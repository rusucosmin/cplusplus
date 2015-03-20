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

using namespace std;

ifstream cin("vulcan.in");
ofstream cout("vulcan.out");

const int MAXN = 100005;
const int oo = (1 << 31) - 1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) {
    if( a > b ) return b;
    return a;
}
const inline int max(const int &a, const int &b) {
    if( a < b ) return b;
    return a;
}
const inline void Get_min(int &a, const int b)    {
    if( a > b ) a = b;
}
const inline void Get_max(int &a, const int b)    {
    if( a < b ) a = b;
}

int N, M, Level[MAXN], LowLink[MAXN];
Graph G;
stack < pair<int, int> > Stack;
set< set<int> > BiconnectedComponents;

inline set<int> CatchBC(const int X, const int Y) {
    set<int> actB;
    pair<int, int> T;
    do {
        T = Stack.top();
        Stack.pop();
        actB.insert(T.first);
        actB.insert(T.second);
    } while(T.first != X || T.second != Y);
    return actB;
}

inline void DFs(int Node, int Father, int actLevel) {
    Level[Node] = LowLink[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it) {
        if(*it == Father)
            continue;
        if(!Level[*it]) {
            Stack.push(make_pair(Node, *it));
            DFs(*it, Node, actLevel + 1);
            Get_min(LowLink[Node], LowLink[*it]);
            if(LowLink[*it] >= Level[Node])
                BiconnectedComponents.insert(CatchBC(Node, *it));
        } else Get_min(LowLink[Node], LowLink[*it]);
    }
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Level[i])
            DFs(i, 0, 1);
    for(set<set<int> > :: iterator i = BiconnectedComponents.begin(), fi = BiconnectedComponents.end() ; i != fi ; ++ i, cout << "\n")
        for(set<int> :: iterator it = i->begin(), j = i->end() ; it != j ; ++ it)
            cout << *it << " ";
    cin.close();
    cout.close();
    return 0;
}
