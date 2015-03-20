#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>

using namespace std;

ifstream cin("erathia.in");
ofstream cout("erathia.out");

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

Graph G;
int N, M, Dad[MAXN];
bitset<MAXN> Used;

inline void DFs(int Node, int Father) {
    Used[Node] = true;
    Dad[Node] = Father;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it) {
        if(*it == Father)
            continue;
        if(!Used[*it])
            DFs(*it, Node);
        else {
            int x = Node;
            cout << "Un ciclu simplu in graful din input: \n";
            cout << *it << " " << x << " " ;
            do {
                x = Dad[x];
                cout << x << " ";
            } while( x != *it );
            exit(0);
        }
    }
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0);
    cin.close();
    cout.close();
    return 0;
}
