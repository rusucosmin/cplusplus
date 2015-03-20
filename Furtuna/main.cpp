#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>
#include <stdio.h>
#include <queue>

using namespace std;

const char infile[] = "furtuna.in";
const char outfile[] = "furtuna.out";

const int MAXN = 405;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, T, W, F[MAXN][MAXN], C[MAXN][MAXN], L[MAXN][MAXN], MAX_COST, maxFlow, where[MAXN], cottage[MAXN], Father[MAXN];
bitset <MAXN> Used;

const int Source = 0;
int Sink = 402;

inline void buildNetwork(const int &time) {
    memset(F, 0, sizeof(F));
    for(int i = 1 ; i <= T ; ++ i)
        for(int j = 1 ; j <= W ; ++ j)
            C[where[i]][cottage[j]] = (L[where[i]][cottage[j]] <= time);
}

inline bool BFs(const int &startNode) {
    queue <int> Q;
    Used.reset();
    Q.push(startNode);
    Used[startNode] = true;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            continue;
        for(int i = 0 ; i <= N + 1 ; ++ i)
            if(!Used[i] && C[Node][i] - F[Node][i] > 0) {
                Used[i] = true;
                Father[i] = Node;
                Q.push(i);
            }
    }
    return Used[Sink];
}

inline void doMaxFlow() {
    while(BFs(Source)) {
        for(int i = 0 ; i <= N + 1 ; ++ i) {
            if(!Used[i] || C[i][Sink] - F[i][Sink] <= 0)
                continue;
            Father[Sink] = i;
            int minFlow = oo;
            for(int j = Sink ; j != Source && minFlow ; j = Father[j])
                minFlow = min(minFlow, C[Father[j]][j] - F[Father[j]][j]);
            if(!minFlow)
                continue;
            for(int j = Sink ; j != Source ; j = Father[j]) {
                F[Father[j]][j] += minFlow;
                F[j][Father[j]] -= minFlow;
            }
            maxFlow += minFlow;
        }
    }
}

inline bool check(const int &time) {
    maxFlow = 0;
    buildNetwork(time);
    doMaxFlow();
    return (maxFlow == T);
}

inline int binarySearch() {
    int Ans = -1;
    int li = 1, ls = MAX_COST * M;
    while( li <= ls ) {
        int mid = ((li + ls) >> 1);
        if(check(mid)) {
            Ans = mid;
            ls = mid - 1;
        }
        else li = mid + 1;
    }
    return Ans;
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d %d %d", &N, &M, &T, &W);
    Sink = N + 1;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        L[x][y] = z;
        L[y][x] = z;
        MAX_COST = max(MAX_COST, z);
    }
    for(int k = 1 ; k <= N ; ++ k)
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= N ; ++ j)
                if(i != j && j != k && k != i && L[i][k] && L[k][j] && ( !L[i][j] || L[i][j] > L[i][k] + L[k][j]))
                    L[i][j] = L[i][k] + L[k][j];
    for(int i = 1 ; i <= T ; ++ i) {
        scanf("%d", &where[i]);
        C[Source][where[i]] = 1;
    }
    for(int i = 1 ; i <= W ; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        cottage[i] = x;
        C[x][Sink] = y;
    }
    printf("%d\n", binarySearch());
    return 0;
}
