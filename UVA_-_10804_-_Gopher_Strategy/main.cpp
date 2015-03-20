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

const int MAXN = 100;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

inline double euclidian(pair<double, double> a, pair<double, double> b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

Graph G;
int N, M, K, mate[MAXN], match[MAXN], T;
double dist[MAXN][MAXN];
bitset <MAXN> Used;

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

inline bool Check(double value) {
    memset(mate, 0, sizeof(mate));
    memset(match, 0, sizeof(match));
    for(int i = 1 ; i <= M ; ++ i) {
        vector <int>().swap(G[i]);
        for(int j = 1 ; j <= N ; ++ j)
            if(dist[i][j] <= value)
                G[i].push_back(j);
    }
    int maxMatching = 0;
    for(bool change = true ; change ; ) {
        change = false;
        Used.reset();
        for(int i = 1 ; i <= M ; ++ i)
            if(!match[i])
                if(pairUp(i)) {
                    ++ maxMatching;
                    change = true;
                }
    }
    return maxMatching >= M - K;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        cin >> M >> N >> K;
        vector<pair<double, double> > A, B;
        A.push_back(make_pair(0, 0));
        B.push_back(make_pair(0, 0));
        for(int i = 1 ; i <= M ; ++ i) {
            double x, y;
            cin >> x >> y;
            A.push_back(make_pair(x, y));
        }
        for(int i = 1 ; i <= N ; ++ i) {
            double x, y;
            cin >> x >> y;
            B.push_back(make_pair(x, y));
        }
        double li, ls;
        ls = li = euclidian(A[1], B[1]);
        for(int i = 1 ; i <= M ; ++ i)
            for(int j = 1 ; j <= N ; ++ j) {
                dist[i][j] = euclidian(A[i], B[j]);
                li = min(li, dist[i][j]);
                ls = max(ls, dist[i][j]);
            }
        cout << "Case #" << test << ":\n";
        if((M == 0 && N == 0) || (M == K) || (M == 0)) {
            cout << "0.000\n\n";
            continue;
        }
        if(M - K > N) {
            cout << "Too bad.\n\n";
            continue;
        }
        while(fabs(ls - li) > 0.0001) {
            double mid = ((li + ls) / 2.0);
            if(Check(mid))
                ls = mid;
            else li = mid;
        }
        cout << fixed << setprecision(3) << sqrt(li) << '\n';
        cout << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
