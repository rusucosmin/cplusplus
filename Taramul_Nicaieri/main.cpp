#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <list>
#include <iomanip>

using namespace std;

string file = "harta";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 2*100+5;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

int N, M, X, Y, C[MAXN][MAXN], F[MAXN][MAXN], Father[MAXN], maxFlow;
Graph G;
bitset <MAXN> Used;
queue<int>Q;

inline bool BFs() {
    Used.reset();
    for(Q.push(0), Used[0] = true ; !Q.empty() ; Q.pop()){
        int Node = Q.front();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && C[Node][*it] > F[Node][*it])
                Q.push(*it), Used[*it] = true, Father[*it] = Node;
    }
    return Used[M];
}

int main() {
    cin >> N;
    M = 2 * N + 1;
    for(int i = 1 ; i <= N ; ++ i) {
        int x, y;
        cin >> x >> y; X += x; Y += y;
        G[0].push_back(i);
        C[0][i] = x;
        G[i+N].push_back(M);
        C[i+N][M] = y;
    }
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = N + 1 ; j < M ; ++ j)
            if(i != j - N) {
                C[i][j] = 1;
                G[i].push_back(j);
                G[j].push_back(i);
            }
    for( ; BFs() ; ) {
        ++ maxFlow;
        for(int i = M ; i ; i = Father[i])
            ++ F[Father[i]][i],
            -- F[i][Father[i]];
    }
    cout << maxFlow << '\n';
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = N + 1; j < M ; ++ j)
            if(F[i][j] == 1)
                cout << i << ' ' << j - N  << '\n';
    cin.close();
    cout.close();
    return 0;
}
