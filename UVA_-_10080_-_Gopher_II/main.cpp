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

int N, M, T, mate[MAXN], match[MAXN], S, V;
bitset <MAXN> Used;
Graph G;

inline double euclidian(pair<double, double> a, pair<double, double> b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

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
    while(cin >> N >> M >> S >> V) {
        double maxDist = (1.0 * V * S) * (1.0 * V * S);
        vector <pair<double, double> > A, B;
        A.push_back(make_pair(0, 0));
        B.push_back(make_pair(0, 0));
        for(int i = 1 ; i <= N ; ++ i) {
            double x, y;
            cin >> x >> y;
            A.push_back(make_pair(x, y));
        }
        for(int i = 1 ; i <= M ; ++ i) {
            double x, y;
            cin >> x >> y;
            B.push_back(make_pair(x, y));
        }
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= M ; ++ j) {
                double dist = euclidian(A[i], B[j]);
                if(dist <= maxDist)
                    G[i].push_back(j);
            }
        cout << N - getMaxMatching(G) << '\n';
        memset(match, 0, sizeof(match));
        memset(mate, 0, sizeof(mate));
    }
    fin.close();
    fout.close();
    return 0;
}
