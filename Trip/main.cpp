#include <stdio.h>
#include <bitset>
#include <string.h>
#include <queue>

using namespace std;

const char outfile[] = "trip.out";
const char infile[] = "trip.in";

const int MAXN = 1004;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

int DFlevel[MAXN], lowLink[MAXN], N, M, S, D, d[MAXN], Father[MAXN];
bitset <MAXN> Used, edge[MAXN], critic[MAXN];
queue <int> bfQ;
Graph G;

void DFs(const int &Node, const int &Father, const int &actLevel) {
    DFlevel[Node] = lowLink[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        if(!DFlevel[*it]) {
            DFs(*it, Node, actLevel + 1);
            lowLink[Node] = min(lowLink[Node], lowLink[*it]);
            if(lowLink[*it] > DFlevel[Node])
                critic[Node][*it] = critic[*it][Node] = 1;
        }
        else lowLink[Node] = min(lowLink[Node], DFlevel[*it]);
    }
}

inline void BFs1(const int &startNode, const int &lastNode) {
    memset(d, oo, sizeof(d));
    d[startNode] = 0;
    for(bfQ.push(startNode); !bfQ.empty() ; bfQ.pop()) {
        int Node = bfQ.front();
        if(Node == lastNode)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(d[*it] > d[Node] + critic[Node][*it]) {
                d[*it] = d[Node] + critic[Node][*it];
                Father[*it] = Node;
                bfQ.push(*it);
            }
    }
}

inline void BFs2(const int &startNode, const int &lastNode) {
    for(bfQ.push(startNode), Used[startNode] = true; !bfQ.empty() ; bfQ.pop()) {
        int Node = bfQ.front();
        if(Node == lastNode)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && (critic[Node][*it] || !edge[Node][*it] )) {
                Used[*it] = true;
                Father[*it] = Node;
                bfQ.push(*it);
            }
    }
}

void Write(const int &actNode) {
    if(Father[actNode]) {
        edge[Father[actNode]][actNode] = 1; edge[actNode][Father[actNode]] = 1;
        Write(Father[actNode]);
    }
    printf("%d ", actNode);
}

int main() {
    freopen(outfile, "w", stdout);
    freopen(infile, "r", stdin);
    scanf("%d %d %d %d", &S, &D, &N, &M);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0, 1);
    BFs1(S, D);
    if(d[D] == oo) {
        printf("-1\n");
        return 0;
    }
    printf("%d\n", d[D]);
    Write(D);
    BFs2(S, D);
    printf("\n");
    for(int j = D ; j != S ; j = Father[j])
        printf("%d ", j);
    printf("%d\n", S);
    return 0;
}
