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

string file = "paznici";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

Graph G;
int N, M, l, L[MAXN], Cuplaj[MAXN], Pereche[MAXN];
bitset<MAXN> Used, sr, sl;

vector<char> v1, v2;

inline bool pairUp(int Node) {
    if(Used[Node])
        return false;
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
        if(!Pereche[*it]) {
            Pereche[*it] = Node;
            Cuplaj[Node] = *it;
            return true;
        }
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
        if(pairUp(Pereche[*it])) {
            Pereche[*it] = Node;
            Cuplaj[Node] = *it;
            return true;
        }
    return false;
}

inline void MinVertexCover() {
    for(bool ok = true ; ok ; ) {
        ok = false;
        Used.reset();
        for(int i = 1 ; i <= l ; ++ i)
                if(!Cuplaj[L[i]])
                    ok |= pairUp(L[i]);
    }
}

inline void support(int Node) {
    for(It it = G[Node].begin(); it != G[Node].end(); ++ it)
        if(!sr[*it]) {
            sr[*it] = 1;
            sl[Pereche[*it]] = 0;
            support(Pereche[*it]);
        }
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j) {
            char c;
            cin >> c;
            if(c == '1') {
                if(!G[i].size())
                    ++l, L[l] = i;
                G[i].push_back(j);
            }
        }
    MinVertexCover();
    for(int i = 1 ; i <= l ; ++ i)
        if(Cuplaj[L[i]])
            sl[L[i]] = true;
    for(int i = 1 ; i <= l ; ++ i)
        if(!sl[L[i]])
            support(L[i]);
    for(int i = 1 ; i <= N ; ++ i)
        if(sl[i])
            cout << (char)(i + 'A' - 1);
    for(int i = 1 ; i <= M ; ++ i)
        if(sr[i])
            cout << (char)(i + 'a' - 1);
    cin.close();
    cout.close();
    return 0;
}
