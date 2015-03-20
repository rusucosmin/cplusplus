/**
    Weird algorithms
*/
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

string file = "joc4";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 2*255;
const int oo = 1000;

typedef vector<short> Graph[MAXN];
typedef vector<short> :: iterator It;

Graph G;
short N, M, A, B, C[MAXN][MAXN], Father[MAXN], maxFlow;
bitset <MAXN> Used;
vector<short>Bv;
queue <short> Q;

inline bool BFs() {
    Used.reset();
    for(Q.push(A+N), Used[A+N] = true, Father[A+N] = 0; !Q.empty() ; Q.pop()) {
        short Node = Q.front();
        for(int i = 2*N ; i ; -- i)
            if(!Used[i] && C[Node][i] > 0)
                Q.push(i), Used[i] = true, Father[i] = Node;
    }
    return Used[B];
}

int main() {
    cin >> N >> M >> A >> B;
    for(int i = 1 ; i <= M ; ++ i) {
        short x, y;
        cin >> x >> y;
        C[x+N][y] = C[y+N][x] = 1;
    }
    for(int i = 1 ; i <= N ; ++ i)
        C[i][N+i] = 1;
    for(; BFs() ; ++ maxFlow) {
        for(int i = B ; Father[i] ; i = Father[i])
            -- C[Father[i]][i];
    }
    cout << maxFlow << '\n';
    cin.close();
    cout.close();
    return 0;
}
