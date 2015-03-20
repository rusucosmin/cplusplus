/**
 *  Actually "ATAC"
 *
 */
#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>
#include <iomanip>

using namespace std;

ifstream cin("atac.in");
ofstream cout("atac.out");


const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

Graph G;
int N, M, ArtPoints, Level[MAXN], LowLink[MAXN], Critics;

inline void DFs(int Node, int Father, int actLevel) {
    Level[Node] = LowLink[Node] = actLevel;
    bool critic = false;
    int sons = 0;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father) continue;
        if(!Level[*it]) {
            DFs(*it, Node, actLevel + 1);
            LowLink[Node] = min(LowLink[Node], LowLink[*it]);
            critic |= (LowLink[*it] >= Level[Node]);
            ++ sons;
        }
        else LowLink[Node] = min(LowLink[Node], Level[*it]);
    }
    if(Father){
        if(critic)
            ++Critics;
    }
    else if(sons > 1)
        ++ Critics;
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
    cout << fixed << setprecision(2) << (double)Critics*100.00 / (double)N << "\n";
    cin.close();
    cout.close();
    return 0;
}
