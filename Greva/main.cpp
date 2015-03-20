#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>

using namespace std;

ifstream cin("greva.in");
ofstream cout("greva.out");

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

Graph G;
int N, M, LowLink[MAXN], Level[MAXN], Critics;
bitset<MAXN> Used, Critic;

inline void DFs(int Node, int Father, int actLevel) {
    Level[Node] = LowLink[Node] = actLevel;
    bool critical = false;
    int sons = 0;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
        if(*it != Father) {
            if(!Level[*it]) {
                DFs(*it, Node, actLevel+1);
                LowLink[Node] = min(LowLink[Node], LowLink[*it]);
                critical |= LowLink[*it] >= Level[Node];
                ++ sons;
            }
            else
                LowLink[Node] = min(LowLink[Node], Level[*it]);
        }
    if(Node != 1) {
        if(critical)
            Critic[Node] = true, ++Critics;
    }
    else if(sons >= 2)
            Critic[Node] = true, ++Critics;
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0, 1);
    if(G[1].size() > 2)
        Critic[1] = false, --Critics;
    cout << N - Critics << "\n";
    for(int i = 1 ; i <= N ; ++ i)
        if(!Critic[i])
            cout << i << " ";
    cin.close();
    cout.close();
    return 0;
}
