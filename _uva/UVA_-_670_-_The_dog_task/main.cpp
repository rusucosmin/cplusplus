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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

vector <pair<int, int> > A, B;
Graph G;
bitset <MAXN> Used;
int N, M, T, mate[MAXN], match[MAXN];

inline int euclidianDistance(pair<int, int> a, pair<int, int> b) {
    return (b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second);
}

inline bool pairUp(int Node) {
    if(Used[Node])
        return false;
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!mate[*it] || pairUp(mate[*it])) {
            mate[*it] = Node;
            match[Node] = *it;
            return true;
        }
    return false;
}

inline int getMaxMatching(Graph &G) {
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
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        cin >> N >> M;
        A.push_back(make_pair(0, 0));
        B.push_back(make_pair(0, 0));
        for(int i = 1 ; i <= N ; ++ i) {
            int x, y;
            cin >> x >> y;
            A.push_back(make_pair(x, y));
        }
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            cin >> x >> y;
            B.push_back(make_pair(x, y));
        }
        for(int i = 1 ; i < N ; ++ i) {
            double x = 2.0 * sqrt(euclidianDistance(A[i], A[i + 1]));
            for(int j = 1 ; j <= M ; ++ j) {
                double len1 = sqrt(euclidianDistance(A[i], B[j]));
                double len2 = sqrt(euclidianDistance(B[j], A[i + 1]));
                if(len1 + len2 <= x)
                    G[i].push_back(j);
            }
        }
        cout << N + getMaxMatching(G) << '\n';
        cout << A[1].first << ' ' << A[1].second;
        if(match[1])
            cout << ' ' << B[match[1]].first << ' ' << B[match[1]].second;
        for(int i = 2 ; i <= N ; ++ i) {
            cout << ' ' << A[i].first << ' ' << A[i].second;
            if(match[i])
                cout << ' ' << B[match[i]].first << ' ' << B[match[i]].second;
        }
        cout << "\n";
        if(T != test)
            cout << "\n";
        memset(mate, 0, sizeof(mate));
        memset(match, 0, sizeof(match));
        for(int i = 1 ; i <= N ; ++ i)
            vector <int> ().swap(G[i]);
        vector <pair<int, int> > ().swap(A);
        vector <pair<int, int> > ().swap(B);
    }
    return 0;
}
