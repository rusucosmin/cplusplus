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

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int dp[MAXN];
int N, M, S, D, P;
Graph G;

inline void buildDP(int stNode) {
    dp[stNode] = oo;
    queue <int> Q;
    Q.push(stNode);
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(dp[it->first] < min(dp[Node], it->second)) {
                dp[it->first] = min(dp[Node], it->second);
                Q.push(it->first);
            }
        }
    }
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int test = 0;
    while(cin >> N >> M) {
        if(!N && !M)
            return 0;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            -- z;
            G[x].push_back(make_pair(y, z));
            G[y].push_back(make_pair(x, z));
        }
        cin >> S >> D >> P;
        buildDP(S);
        cout << "Scenario #" << ++ test << "\n";
        cout << "Minimum Number of Trips = " << (P / dp[D]) + ((P % dp[D]) > 0) << "\n\n";
        for(int i = 1 ; i <= N ; ++ i) {
            vector<pair<int, int> > ().swap(G[i]);
            dp[i] = 0;
        }
    }
    return 0;
}
