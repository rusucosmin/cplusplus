#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>

using namespace std;

ifstream cin("neutroni.in");
ofstream cout("neutroni.out");

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

Graph G;
int N, M, K, Level[MAXN], LowLink[MAXN];
vector<int> artPoint;

inline void DFs(int Node, int Father, int actLevel) {
    bool critical = false ; int sons = 0;
    Level[Node] = LowLink[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it) {
        if(*it == Father)
            continue;
        if(!Level[*it]) {
            DFs(*it, Node, actLevel+1);
            LowLink[Node] = min(LowLink[Node], LowLink[*it]);
            critical |= (LowLink[*it] >= Level[Node]);
            ++ sons;
        }
        else
            LowLink[Node] = min(LowLink[Node], Level[*it]);
    }
    if(Father) {
        if(critical)
            artPoint.push_back(Node);
    }
    else if(sons > 1)
        artPoint.push_back(Node);

}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Level[i])
            DFs(i, 0, 1), ++ K;
    cout << K << " " << artPoint.size() << "\n";
    for(It it = artPoint.begin(), fin = artPoint.end() ; it != fin ; ++ it)
        cout << *it << " ";
    cin.close();
    cout.close();
    return 0;
}
