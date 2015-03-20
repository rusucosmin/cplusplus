#include <fstream>
#include <bitset>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

ifstream cin("mvc.in");
ofstream cout("mvc.out");

const int MAXN = 100005;

typedef vector<int> Graph[MAXN];
typedef vector<int>::iterator It;

Graph G;
bitset<MAXN> Used;
int c[MAXN], Dad[MAXN], Cys, Cyd, N, dp[MAXN][2];
queue <int> Q;

inline void BFs(int SNode) {
    for(Q.push(SNode); !Q.empty(); Q.pop()) {
        int Node = Q.front();
        Used[Node] = true;
        for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
            if(!Used[*it])
                Q.push(*it), Dad[*it] = Node;
            else if(Dad[Node] != *it)   /// Muchia "de intoarcere" :)
                    Cys = Node, Cyd = *it;
    }
    Used.reset();
}

inline void DFs(int Node) {
    Used[Node] = true;
    dp[Node][1] = c[Node];
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it] && (Dad[*it] == Node || Dad[Node] == *it)){
            DFs(*it);
            dp[Node][0] += dp[*it][1];
            dp[Node][1] += min(dp[*it][0], dp[*it][1]);
        }
}

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> c[i];
    for(int i = 1 ; i <= N ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    BFs(1); ///aflu ciclul
    int sol = (1<<31)-1;
    DFs(Cys);
    Used.reset();
    sol = min(sol, dp[Cys][1]);
    memset(dp, 0, sizeof(dp));
    DFs(Cyd);
    sol = min(sol, dp[Cyd][1]);
    cout << sol << "\n";
    cin.close();
    cout.close();
    return 0;
}
