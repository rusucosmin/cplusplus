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

const char infile[] = "input.txt";
const char outfile[] = "output.txt";

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

inline bool isOk(int conf) {
    int ret = 0;
    while(conf) {
        ++ ret;
        conf &= (conf - 1);
    }
    return ret <= 4;
}

int N, M, mate[MAXN], match[MAXN];
map<string, int> mp;
map<int, string> inv;
bitset <MAXN> Used;
Graph G;

inline bool pairUp(int Node) {
    if(Used[Node])
        return 0;
    Used[Node] = 1;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
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
        for(int i = 1 ; i <= N ; ++ i)
            if(!match[i] && pairUp(i)) {
                ++ maxMatching;
                change = true;
            }
    }
    return maxMatching;
}

int main() {
    cin.sync_with_stdio(false);
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        string a;
        cin >> a;
        int sz = a.size();
        for(int conf = 1 ; conf < (1 << sz) ; ++ conf) {
            if(isOk(conf)) {
                string s;
                for(int j = 0 ; j < sz ; ++ j)
                    if(conf & (1 << j))
                        s += a[j];
                if(!mp[s]) {
                    mp[s] = ++ M;
                    inv[M] = s;
                }
                G[i].push_back(mp[s]);
            }
        }
    }
    if(getMaxMatching(G) != N) {
        cout << "-1\n";
        return 0;
    }
    for(int i = 1 ; i <= N ; ++ i)
        cout << inv[match[i]] << '\n';
    return 0;
}
