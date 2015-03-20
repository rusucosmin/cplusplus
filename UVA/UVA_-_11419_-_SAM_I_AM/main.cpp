#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int R, C, N, L[MAXN], mate[MAXN], match[MAXN];
Graph G;
bitset<MAXN> Used, sl, sr;

inline bool pairUp(int Node) {
    if(Used[Node])
        return 0;
    Used[Node] = 1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!mate[*it] || pairUp(mate[*it])) {
            mate[*it] = Node;
            match[Node] = *it;
            return 1;
        }
    return 0;
}

inline int getMaxMatching(Graph &G) {
    int maxMatching = 0;
    for(bool change = true ; change ; ) {
        change = false;
        Used.reset();
        for(int i = 1 ; i <= L[0] ; ++ i)
            if(!match[L[i]])
                if(pairUp(L[i])) {
                    ++maxMatching;
                    change = true;
                }
    }
    return maxMatching;
}

inline void minVertexCover(int Node) {
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!sr[*it]) {
            sr[*it] = 1;
            sl[mate[*it]] = 0;
            minVertexCover(mate[*it]);
        }
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(cin >> R >> C >> N) {
        if(!R && !C && !N)
            return 0;
        for(int i = 1 ; i <= N ; ++ i) {
            int x, y;
            cin >> x >> y;
            if(!G[x].size())
                L[++ L[0]] = x;
            G[x].push_back(y);
        }
        cout << getMaxMatching(G) << ' ';
        for(int i = 1 ; i <= L[0] ; ++ i)
            if(match[L[i]])
                sl[L[i]] = 1;
        for(int i = 1 ; i <= L[0] ; ++ i)
            if(!sl[L[i]])
                minVertexCover(L[i]);
        for(int i = 1 ; i <= R ; ++ i) {
            if(sl[i])
                cout << "r" << i << " ";
            vector <int>().swap(G[i]);
        }
        for(int i = 1 ; i <= C ; ++ i)
            if(sr[i])
                cout << "c" << i << " ";
        cout << '\n';
        memset(mate, 0, sizeof(mate));
        memset(match, 0, sizeof(match));
        sl.reset();
        sr.reset();
        L[0] = 0;
    }
    fin.close();
    fout.close();
    return 0;
}
