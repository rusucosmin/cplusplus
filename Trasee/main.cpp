#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>

using namespace std;

ifstream cin("trasee.in");
ofstream cout("trasee.out");

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

Graph G;
int N, M, Father[MAXN], Level[MAXN];
bitset<MAXN> Used;

inline void WriteCycle(int X, int Y) {
    cout << Level[X] - Level[Y] + 1 << " " << X << " ";
    do{
        X = Father[X];
        cout << X << " ";
    }while(X != Y);
    cout << "\n";
}

inline void DFs(int Node, int actLevel, int Dad) {
    Used[Node] = true;
    Level[Node] = actLevel;
    Father[Node] = Dad;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
        if(!Used[*it])
            DFs(*it, actLevel+1, Node);
        else if( *it != Dad && Level[*it] < Level[Node])
            WriteCycle(Node, *it);
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i ) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    cout << M - N + 1 << '\n';
    DFs(1, 0, 0);
    cin.close();
    cout.close();
    return 0;
}
