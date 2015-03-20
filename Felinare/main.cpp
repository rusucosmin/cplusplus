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

string file = "felinare";

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

int N, M, Cuplaj[MAXN], Pereche[MAXN], MaxF;
Graph G;
bitset<MAXN> Used, sl, sr;

inline bool pairUp(int Node) {
    if(Used[Node])
        return false;
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
        if(!Pereche[*it] || pairUp(Pereche[*it])) {
            Pereche[*it] = Node;
            Cuplaj[Node] = *it;
            return true;
        }
    return false;
}

inline void MM() {
    for(bool ok = true ; ok ; ) {
        ok = false;
        Used.reset();
        for(int i = 1 ; i <= N ; ++ i)
            if(!Cuplaj[i])
                ok |= pairUp(i);
    }
}

inline void Support(int Node) {
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it) {
        if(!sr[*it]) {
            sr[*it] = true;
            sl[Pereche[*it]] = false;
            Support(Pereche[*it]);
        }
    }
}

inline void MVC() {
    for(int i = 1 ; i <= N ; ++ i)
        if(Cuplaj[i])
            sl[i] = true;
    for(int i = 1 ; i <= N ; ++ i)
        if(!sl[i])
            Support(i);
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
    }
    MM();
    MVC();
    for(int i = 1 ; i <= N ; ++ i) {
        if(!sl[i])
            ++ MaxF;
        if(!sr[i])
            ++ MaxF;
    }
    cout << MaxF << '\n';
    for(int i = 1 ; i <= N ; ++ i) {
        if(sl[i] && sr[i])
            cout << "0\n";
        else
        if(!sl[i] && !sr[i])
            cout << "3\n";
        else if(sl[i] && !sr[i])
            cout << "2\n";
            else cout << "1\n";
    }
    cin.close();
    cout.close();
    return 0;
}
