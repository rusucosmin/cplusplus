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

const inline int min(const int &a, const int &b) {
    if( a > b ) return b;
    return a;
}
const inline int max(const int &a, const int &b) {
    if( a < b ) return b;
    return a;
}
const inline void Get_min(int &a, const int b)    {
    if( a > b ) a = b;
}
const inline void Get_max(int &a, const int b)    {
    if( a < b ) a = b;
}

int N, M, T, L, R, K;
Graph G;
int mate[MAXN], match[MAXN];
double dist[MAXN][MAXN];
bitset <MAXN> Used;

inline int euclidianDistance(pair<int, int> a, pair<int, int> b) {
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

inline bool Check(int value) {
    memset(mate, 0, sizeof(mate));
    memset(match, 0, sizeof(match));
    for(int i = 1 ; i <= L ; ++ i) {
        vector <int>().swap(G[i]);
        for(int j = 1 ; j <= R ; ++ j)
            if(dist[i][j] <= value)
                G[i].push_back(j);
    }
    int maxMatching = 0;
    for(bool change = true ; change ; ) {
        change = false;
        Used.reset();
        for(int i = 1 ; i <= L ; ++ i)
            if(!match[i])
                if(pairUp(i)) {
                    ++ maxMatching;
                    change = true;
                }
    }
    return maxMatching >= K;
}

int main() {
    cin.sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
#endif
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        vector<pair<int, int> > A, B;
        A.push_back(make_pair(0, 0));
        B.push_back(make_pair(0, 0));
        cin >> N >> K;
        for(int i = 1 ; i <= N ; ++ i) {
            int a, b;
            string c;
            cin >> a >> b >> c;
            if(c == "red")
                A.push_back(make_pair(a, b));
            if(c == "blue")
                B.push_back(make_pair(a, b));
        }
        L = A.size() - 1;
        R = B.size() - 1;
        int li = floor(sqrt(euclidianDistance(A[1], B[1])));
        int ls = ceil(sqrt(euclidianDistance(A[1], B[1])));
        for(int i = 1 ; i <= L ; ++ i)
            for(int j = 1 ; j <= R ; ++ j) {
                dist[i][j] = sqrt(euclidianDistance(A[i], B[j]));
                li = min(li, floor(dist[i][j]));
                ls = max(ls, ceil(dist[i][j]));
            }
        int Ans = -1;
        while(li <= ls) {
            int mid = ((li + ls) >> 1);
            ///cerr << li << ' ' << ls << '\n';
            if(Check(mid)) {
                Ans = mid;
                ls = mid - 1;
            } else li = mid + 1;
        }
        if(Ans != -1)
            cout << Ans << '\n';
        else cout << "Impossible\n";
    }
    return 0;
}
