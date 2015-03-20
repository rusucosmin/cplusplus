#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const char infile[] = "benzina2.in";
const char outfile[] = "benzina2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 5005;
const int MAXK = 55;
const int oo = 0x3f3f3f3f;

typedef pair<int, int> edge;
typedef vector< edge > Graph[MAXN];
typedef vector< edge > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
priority_queue <pair<int, edge>, vector <pair< int, edge > >, greater < pair<int, edge > > > Q;
int dp[MAXN][MAXK], Father[MAXN];

inline void Dijkstra(const int &firstNode, const int &lastNode, const int &K) {
    memset(dp, oo, sizeof(dp));
    dp[firstNode][0] = 0;
    Q.push(make_pair(0, make_pair(firstNode, 0)));
    while( !Q.empty() ) {
        int actCost = Q.top().first;
        int Node = Q.top().second.first;
        int actRest = Q.top().second.second;
        Q.pop();
        if(Node == lastNode && !actRest) {
            fout << actCost << '\n';
            return;
        }
        if(dp[Node][actRest] < actCost)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            int newNode = it->first;
            int newCost = it->second;
            int newRest = (actRest + newCost) % K;
            if(dp[newNode][newRest] > actCost + newCost) {
                dp[newNode][newRest] = actCost + newCost;
                Q.push(make_pair(dp[newNode][newRest], make_pair(newNode, newRest)));
            }
        }
    }
}

void findPath(const int Node, const int actRest, const int K, const int lastNode) {
    //if(Node == lastNode) {
    //    fout << Node << ' ';
    //    return ;
    //}
    int next = oo, restnext = 0;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        int newNode = it->first;
        int y = it->second;
        int x = K * (y / K) + actRest - y;
        x %= K;
        if(x >= 0 && dp[newNode][x] + y == dp[Node][actRest])
            if(next > newNode) {
                next = newNode;
                restnext = x;
            }
        x = K * (y / K + 1) + actRest - y;
        x %= K;
        if(x >= 0 && dp[newNode][x] + y == dp[Node][actRest])
            if(next > newNode) {
                next = newNode;
                restnext = x;
            }
    }
    if(next != oo)
        findPath(next, restnext, K, lastNode);
    fout << Node << ' ';
}

int main() {
    int N, M, A, B, K;
    fin >> N >> K >> A >> B;
    fin >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, k;
        fin >> x >> y >> k;
        G[x].push_back(make_pair(y, k));
        G[y].push_back(make_pair(x, k));
    }
    Dijkstra(A, B, K);
    findPath(B, 0, K, A);
    fin.close();
    fout.close();
    return 0;
}
