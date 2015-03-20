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

const int MAXN = 305;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN * MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char s[MAXN][MAXN];
int a[MAXN][MAXN], b[MAXN][MAXN];
int L, R, T, N, M;
Graph G;
bitset <MAXN * MAXN> Used;
int match[MAXN * MAXN], mate[MAXN * MAXN];

inline bool pairUp(Graph &G, int Node) {
    if(Used[Node])
        return 0;
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!mate[*it] || pairUp(G, mate[*it])) {
            mate[*it] = Node;
            match[Node] = *it;
            return 1;
        }
    return 0;
}

inline int getMaximumMatching(Graph &G, int L, int R) {
    int maxMatching = 0;
    for(bool change = true ; change ; ) {
        change = false;
        Used.reset();
        for(int i = 1 ; i <= L ; ++ i)
            if(!match[i])
                if(pairUp(G, i)) {
                    ++ maxMatching;
                    change = true;
                }
    }
    return maxMatching;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        L = R = 0;
        cin >> N >> M;
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= M ; ++ j) {
                cin >> s[i][j];
                if(s[i][j] != 'A') {
                    if(j == 1 || s[i][j - 1] == 'A')
                        a[i][j] = ++ L;
                    else a[i][j] = a[i][j - 1];
                    if(i == 1 || s[i - 1][j] == 'A')
                        b[i][j] = ++ R;
                    else b[i][j] = b[i - 1][j];
                    if(s[i][j] == 'H')
                        G[a[i][j]].push_back(b[i][j]);
                }
            }
        cout << getMaximumMatching(G, L, R) << '\n';
        for(int i = 1 ; i <= L ; ++ i)
            vector <int>().swap(G[i]);
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(match, 0, sizeof(match));
        memset(mate, 0, sizeof(mate));
    }
    return 0;
}
