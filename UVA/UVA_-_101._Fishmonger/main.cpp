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

const int MAXN = 55;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct state {
    int node, t, cost;
    node () {}

    node(int _pos, int _t, int _cost) {
        pos = _pos;
        t = _t;
        cost = _cost;
    }
    inline bool operator < (const state & other) const {
        if(cost == state.cost)
            return t > other.t;
        return cost > state.cost;
    }
};

int dist[MAXN][MAXN];
int cost[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(cin >> N >> T) {
        if(!N && !T)
            return;
        priority_queue <node> Q;
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= N ; ++ j)
                cin >> dist[i][j];
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= N ; ++ j)
                cin >> cost[i][j];
        memset(dp, oo, sizeof(dp));
        Q.push(state(1, 0, 0));
        while(!Q.empty()) {
            int Node = Q.top().node;
            int timp = Q.top().t;
            int cost = Q.top().cost;
            Q.pop();
            if(dp[Node][timp])

        }
    }
    fin.close();
    fout.close();
    return 0;
}
