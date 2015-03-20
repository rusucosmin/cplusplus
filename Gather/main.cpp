#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <queue>

using namespace std;

const int maxn = 755;
const int maxk = 16;
const int maxm = 1255;
const int oo = 0x3f3f3f3f;

struct edge {
    int x, y, z;
    edge(int _x, int _y, int _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};

int k, n, m;
int dmin[maxk][maxk][maxk];   /// dp[i][k][j] = distanta minima de la nodul s[i] la nodul s[j], trcand prin muchii cu capacitatea >= j
                            /// adica trecand cu k prizonieri
vector <edge> g[maxn];
vector <int> s;

priority_queue <pair<int, int> > q;
int dist[maxn], dp[1 << maxk][maxk];

inline void dijkstra(int stnode, int cnt, int best[maxk]) {
    memset(dist, oo, sizeof(dist));
    dist[stnode] = 0;
    q.push(make_pair(0, stnode));
    while(!q.empty()) {
        int node = q.top().second;
        int cost = -q.top().first;
        q.pop();
        if(dist[node] < cost)
            continue;
        for(vector <edge> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
            if(dist[it->x] > dist[node] + it->y && it->z >= cnt) {
                dist[it->x] = dist[node] + it->y;
                q.push(make_pair(-dist[it->x], it->x));
            }
    }
    for(int i = 0 ; i < k ; ++ i)
        best[i] = dist[s[i]];
}

inline int bitcount(int conf) {
    int ret = 0;
    while(conf) {
        conf = (conf & (conf - 1));
        ++ ret;
    }
    return ret;
}

int main() {
    ifstream fin("gather.in");
    ofstream fout("gather.out");

    fin >> k >> n >> m;
    s.push_back(0);
    for(int i = 1 ; i <= k ; ++ i) {
        int x;
        fin >> x;
        -- x;
        s.push_back(x);
    }
    k = s.size(); /// k = k + 1
    for(int i = 1 ; i <= m ; ++ i) {
        int a, b, c, d;
        fin >> a >> b >> c >> d;
        -- a; -- b;
        g[a].push_back(edge(b, c, d));
        g[b].push_back(edge(a, c, d));
    }
    for(int i = 0 ; i < k ; ++ i)
        for(int j = 0 ; j < k ; ++ j)
            dijkstra(s[i], j, dmin[i][j]);
    int maxmask = (1 << k);
    memset(dp, oo, sizeof(dp));
    dp[1][0] = 0;
    for(int mask = 1 ; mask < maxmask ; ++ mask) {
        int bitcnt = bitcount(mask);
        for(int i = 0 ; i < k ; ++ i)
            if(mask & (1 << i))
                for(int j = 0 ; j < k ; ++ j)
                    if(mask & (1 << j) && dmin[j][bitcnt - 2][i] != oo)
                        dp[mask][i] = min(dp[mask][i], dp[mask ^ (1 << i)][j] + (bitcnt - 1) * dmin[j][bitcnt - 2][i]); /// vin bitcnt - 1 oameni (fara cel din i)
    }                                                                                                        /// si din aia il scad pe gigel, deci -2
    int ans = 0x3f3f3f3f;
    for(int i = 0 ; i < k ; ++ i)
        ans = min(ans, dp[maxmask - 1][i]);
    fout << ans << '\n';
}
