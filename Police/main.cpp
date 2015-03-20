#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

const char infile[] = "police.in";
const char outfile[] = "police.out";

const int MAXN = 4005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, Father[MAXN], Level[MAXN];
Graph G;
bitset <MAXN> Used;
vector <vector<int> > v;

inline void cacheCycle(int Node, const int &Ancestor) {
    vector <int> a;
    if(Level[Node] <= Level[Ancestor])
        return;
    a.push_back(Ancestor);
    while(Level[Node] > Level[Ancestor]) {
        a.push_back(Node);
        Node = Father[Node];
    }
    a.push_back(Node);
    v.push_back(a);
}

void DFs(const int &Node, const int &actLevel, const int &Dad) {
    Used[Node] = true;
    Level[Node] = actLevel;
    Father[Node] = Dad;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Dad)
            continue;
        if(!Used[*it]) {
            DFs(*it, actLevel+1, Node);
        }
        else cacheCycle(Node, *it);
    }
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d", &N, &M);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i) {
        if(!Used[i]) {
            DFs(i, 1, 0);
        }
    }
    printf("%d", (int)v.size());
    for(int i = 0 ; i < v.size() ; ++ i) {
        printf("\n");
        reverse(v[i].begin(), v[i].end());
        for(int j = 0 ; j < v[i].size() ; ++ j)
            printf("%d ", v[i][j]);
    }
    return 0;
}
