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

const int MAXN = 505;
const int oo = 0x3f3f3f3f;

struct trio {
    int nxt, edge, cost;
    trio(int _nxt, int _cost, int _edge) {
        nxt = _nxt;
        cost = _cost;
        edge = _edge;
    }
};

typedef vector< trio > Graph[MAXN];
typedef vector< trio > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
bitset <MAXN> Used[MAXN];
int dp[MAXN], N, M, S, D;
int Father[MAXN];

inline bool Dijkstra() {
    priority_queue <pair<int, int> , vector<pair<int, int> > , greater <pair<int, int> > > Q;
    memset(dp, oo, sizeof(dp));
    dp[S] = 0;
    Q.push(make_pair(0, S));
    memset(Father, 0, sizeof(Father));
    while(!Q.empty()) {
        int Node = Q.top().second;
        int cost = Q.top().first;
        Q.pop();
        if(dp[Node] < cost)
            continue;
        if(Node == D)
            return true;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[Node][it->nxt] && dp[it->nxt] > cost + it->cost) {
                dp[it->nxt] = cost + it->cost;
                Father[it->nxt] = Node;
                Q.push(make_pair(dp[it->nxt], it->nxt));
            }
    }
    return false;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    while(cin >> N >> M) {
        if(!N && !M)
            return 0;
        cin >> S >> D;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            G[x].push_back(trio(y, z, i));
        }
        int Ans = oo;
        while(Dijkstra()) {
            if(Ans == oo)
                Ans = dp[D];
            else if(dp[D] != Ans) {
                Ans = dp[D];
                break;
            }
            for(int i = D ; i != S ; i = Father[i]) {
                cerr << i << ' ' << Father[i] << ' ';
                Used[Father[i]][i] = true;
            }
        }
        Dijkstra();
        if(dp[D] == oo || Ans == oo)
            cout << "-1\n";
        else cout << Ans << '\n';
        for(int i = 0 ; i < N ; ++ i) {
            vector < trio > ().swap(G[i]);
            Used[i].reset();
        }
    }
    fin.close();
    fout.close();
    return 0;
}
