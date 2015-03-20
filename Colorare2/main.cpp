#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <cassert>

using namespace std;

ifstream cin("colorare2.in");
ofstream cout("colorare2.out");

const int MAXN = 205;
const int MAXK = 2505;

typedef vector< pair<int, int> > :: iterator It;

int N, M, K, edgeColor[MAXK], C;
vector < pair<int, int> > G[MAXN];
queue <int> Q;
bitset <MAXN> usedNode;
bitset <MAXN> usedColors;

inline void BFs(int st) {
    Q.push(st);
    for( ; !Q.empty() ; Q.pop()) {
        int Node = Q.front();
        usedColors.reset();
        usedNode[Node] = 1;
        for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it) {
            if( !edgeColor[it->second] ) {
                for(int i = 1 ; i <= MAXN - 5 && !edgeColor[it->second] ; ++ i)
                    if(!usedColors[i]) {
                        C = max(C, i);
                        usedColors[i] = 1;
                        edgeColor[it->second] = i;
                        Q.push(it->first);
                    }
            }
            else usedColors[edgeColor[it->second]] = 1;
        }
    }
}

int main() {
    cin >> N >> M >> K;
    for(int i = 1 ; i <= K ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(make_pair(y, i));
        G[y].push_back(make_pair(x, i));
    }
    for(int i = 1 ; i <= N + M ; ++ i)
        if(!usedNode[i])
            BFs(i);
    cout << C << '\n';
    for(int i = 1 ; i <= K ; ++ i)
        //if(!edgeColor[i])
        //    cout << "1\n";
        //else
        //assert(edgeColor[i] != 0);
            cout << edgeColor[i] << '\n';
    return 0;
}
