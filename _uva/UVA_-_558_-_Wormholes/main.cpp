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

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, T, M;
int inQs[MAXN];
bitset <MAXN> inQ;
int dp[MAXN];
Graph G;

inline bool BellmanFord(int stNode) {
    queue <int> Q;
    Q.push(stNode);
    dp[stNode] = 0;
    inQ[stNode] = 1;
    inQs[stNode] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        inQ[Node] = false;
        Q.pop();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(dp[it->first] > dp[Node] + it->second) {
                dp[it->first] = dp[Node] + it->second;
                if(!inQ[it->first]) {
                    inQ[it->first] = 1;
                    ++ inQs[it->first];
                    if(inQs[it->first] > N)
                        return 1;
                    Q.push(it->first);
                }
            }
    }
    return 0;
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
        for(int i = 1 ; i <= N ; ++ i) {
            vector <pair<int, int> >().swap(G[i]);
            dp[i] = oo;
            inQ[i] = 0;
            inQs[i] = 0;
        }
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            ++ x;
            ++ y;
            G[x].push_back(make_pair(y, z));
        }
        if(BellmanFord(1))
            cout << "possible\n";
        else cout << "not possible\n";
    }
    return 0;
}
