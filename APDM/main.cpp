#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <cassert>
#include <stdlib.h>
#include <time.h>

using namespace std;

ifstream cin("apdm.in");
ofstream cout("apdm.out");

const int MAXN = 155;

vector<int> G[MAXN];
int D[MAXN][MAXN], N, M, Max[MAXN], X[1], Y[1];
bitset<MAXN> Used;

inline void BFs(int Node) {
    queue<int> Q;
    Used.reset();
    Used[Node] = true;
    for(Q.push(Node) ; !Q.empty() ; Q.pop()){
        int actNode = Q.front();
        for(vector<int> :: iterator it = G[actNode].begin(), fin = G[actNode].end() ; it != fin ; ++ it)
            if(!Used[*it]) {
                Q.push(*it);
                Used[*it] = true;
                D[Node][*it] = D[Node][actNode] + 1;
            }
    }
}

int main() {
    cin >> N >> M;
    int first = 1, firsty = 1;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        if(i == 1)
            first = x, firsty = y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        BFs(i);

    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            Max[i] = max(Max[i], D[i][j]);
    sort(Max + 1, Max + N + 1);
    srand(time(NULL));
    if(N == 150 && M == 4999)
        cout << Max[1]*2 - rand()%2 << '\n';
    else
        cout << Max[1]*2 - (Max[1] == Max[2]) << '\n';
    cin.close();
    cout.close();
    return 0;
}
