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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, T, L[MAXN], match[MAXN], mate[MAXN];
Graph G;
bitset <MAXN> Used;

inline bool pairUp(int Node) {
    if(Used[Node])
        return false;
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(!mate[*it] || pairUp(mate[*it])) {
            mate[*it] = Node;
            match[Node] = *it;
            return true;
        }
    }
    return false;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        cin >> N;
        for(int i = 1 ; i <= N ; ++ i) {
            int x, y;
            cin >> x >> y;
            ++ x;
            ++ y;
            if(!G[x].size())
                L[++ L[0]] = x;
            G[x].push_back(y);
        }
        int maxMatching = 0;
        ///cerr << L[0] << '\n';
        for(bool change = true ; change ; ) {
            change = false;
            Used.reset();
            for(int i = 1 ; i <= L[0] ; ++ i)
                if(!match[L[i]])
                    if(pairUp(L[i])) {
                        ++ maxMatching;
                        change = true;
                    }
        }
        cout << maxMatching << '\n';
        memset(mate, 0, sizeof(mate));
        memset(match, 0, sizeof(match));
        for(int i = 1 ; i <= L[0] ; ++ i)
            vector <int> ().swap(G[L[i]]);
        L[0] = 0;
    }
    fin.close();
    fout.close();
    return 0;
}
