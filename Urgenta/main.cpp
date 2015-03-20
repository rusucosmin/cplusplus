#include <fstream>
#include <set>
#include <bitset>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//ifstream cin("urgenta.in");
//ofstream cout("urgenta.out");

const int MAXN = 260;
const int MAXM = 32390;

struct triple{
       int x, y, c;
       triple(int _x, int _y, int _c): x(_x), y(_y), c(_c) {}
};

struct ClassComp{
       inline bool operator () (const triple &a, const triple &b) const {
              return a.c < b.c;
       }
};

vector<triple> G;
int N, M, K;
int Father[MAXN], Apm_edge, Apm_cost, Total_cost;
bool Used[MAXN][MAXN];

inline int Find(int x) {
    if (Father[x] != x)
        Father[x] = Find(Father[x]);
    return Father[x];
}
inline void APM() {
    for(int i = 0 ; i < M ; ++ i) {
        int x = G[i].x;
        int y = G[i].y;
        int c = G[i].c;
        int Tx = Find(x);
        int Ty = Find(y);
        if(Tx != Ty) {
            Father[Tx] = Ty;
            Apm_cost += c;
            ++ Apm_edge;
            Used[x][y] = true;
        }
    }
}
int main() {
    freopen("urgenta.in", "r", stdin);
    freopen("urgenta.out", "w", stdout);
    scanf("%d %d %d", &N, &M, &K);
    //cin >> N >> M >> K;
    for(int i = 1; i <= M ; ++ i) {
        int x, y, c;
        scanf("%d %d %d", &x, &y, &c);
        //cin >> x >> y >> c;
        Total_cost += c;
        G.push_back(triple(x, y, c));
    }
    for(int i = 1 ; i <= N ; ++ i)
        Father[i] = i;
    sort(G.begin(), G.end(), ClassComp());
    APM();
    int Ans = Total_cost - Apm_cost;
    int Ans2 = M - Apm_edge + K - 1;
    for(int i = M - 1 ; i != -1 ; -- i) {
        int x = G[i].x;
        int y = G[i].y;
        int c = G[i].c;
        if(Used[x][y]) {
               -- K;
               Ans += c;
               Used[x][y] = 0;
        }
        if( K == 1 )
            break;
    }
    printf("%d\n%d\n", Ans, Ans2);
    //cout << Ans << '\n' << Ans2 << '\n';
    for(int i = 0 ; i < M ; ++ i)
        if(!Used[G[i].x][G[i].y])
            printf("%d %d\n", G[i].x, G[i].y);
    return 0;
}
