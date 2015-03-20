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

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, K, C, dist[MAXN][MAXN], match[MAXN], mate[MAXN * 2];
bool G[MAXN][2*MAXN];
bitset <MAXN> Used;

inline bool pairUp(int Node) {
    if(Used[Node])
        return false;
    Used[Node] = true;
    for(int i = 1 ; i <= 2 * M ; ++ i)
        if(G[Node][i])
            if(!mate[i] || pairUp(mate[i])) {
                mate[i] = Node;
                match[Node] = i;
                return true;
            }
    return false;
}

inline int getMaximumMatching(int maxVal) {
    memset(G, 0, sizeof(G));
    memset(mate, 0, sizeof(mate));
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j <= M ; ++ j) {
            if(dist[i][j] + C <= maxVal)
                G[i][j] = 1;
            if(dist[i][j] <= maxVal)
                G[i][j + M] = 1;
        }
        match[i] = 0;
    }
    int maxMatching = 0;
    for(bool change = true ; change ; ) {
        change = false;
        Used.reset();
        for(int i = 1 ; i <= N ; ++ i)
            if(!match[i])
                if(pairUp(i)) {
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
    int T;
    for(cin >> T ; T -- ;) {
        int ls = 0;
        cin >> N >> M >> K >> C;
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= M ; ++ j) {
                cin >> dist[i][j];
                ls = max(ls, dist[i][j] + C);
            }
        int li = 0;
        int Ans = 0;
        while(li <= ls) {
            int mid = ((li + ls) >> 1);
            if(getMaximumMatching(mid) >= K){
                ls = mid - 1;
                Ans = mid;
            }
            else li = mid + 1;
        }
        cout << Ans << '\n';
    }
    return 0;
}
