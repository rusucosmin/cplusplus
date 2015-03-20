#include <stdio.h>
#include <bitset>
#include <vector>

using namespace std;

const char infile[] = "pioni.in";
const char outfile[] = "pioni.out";

const int MAXN = 20005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

bitset <MAXN> Used, win;
int fat[MAXN];
Graph G;

void DFs(const int &Node) {
    Used[Node] = true;
    for(vector<int> :: iterator it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(!Used[*it])
            DFs(*it);
        if(!win[*it]) {
            win[Node] = true;
            fat[Node] = *it;
        }
    }
}

int main() {
    int T, N, M;
    vector <int> Path;
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d %d", &T, &N, &M);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
    }
    for(int i = 1 ; i <= N ; ++ i) {
        if(!Used[i]) {
            DFs(i);
        }
    }
    int K, pion;
    while(true) {
        if(!T)
            return 0;
        -- T;
        Path.clear();
        scanf("%d", &K);
        for(int i = 1 ; i <= K ; ++ i) {
            scanf("%d", &pion);
            if(win[pion]) {
                Path.push_back(pion);
                Path.push_back(fat[pion]);
            }
        }
        if(Path.empty()) {
            printf("Fumeanu\n");
            continue;
        }
        printf("Nargy\n");//%d ", Path.size() / 2);
        //for(int i = 0 , sz = Path.size() ; i < sz ; ++ i)
        //    printf("%d ", Path[i]);
        //printf("\n");
    }
}
