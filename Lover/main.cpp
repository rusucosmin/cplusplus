#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "lover.in";
const char outfile[] = "lover.out";

const int MAXN = 3005;
const int MAXK = 305;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, K;
Graph G;
int dp[MAXN][MAXK];

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d %d", &N, &M, &K);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    memset(dp, oo, sizeof(dp));
    dp[1][0] = 0; /// distanta minima din nodul 1 in nodul i, avand ramasi j litrii in rezervor
    for(int i = 1 ; i < N ; ++ i)
        scanf("%d", &P[i]);
    queue <pair<int, int> > Q;
    Q.push(make_pair(1, 0));
    while(!Q.empty()) {
        int Node = Q.front().first;
        int act = Q.front().secind;
        Q.pop();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {

        }
    }
    return 0;
}
