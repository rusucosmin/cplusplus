#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <queue>
#include <bitset>

using namespace std;

ifstream fin("apm.in");
ofstream fout("apm.out");

const int maxn = 200005;
const int oo = 0x3f3f3f3f;

int n, m, father[maxn], dist[maxn];
vector <pair<int, pair<int, int> > > edges;
vector <pair<int, int> > g[maxn];
bitset <maxn> used;

inline int getsize() {
    return (sizeof(n) + sizeof(m) + sizeof(father) + sizeof(edges) + sizeof(g) + sizeof(dist)) / 1024;
}

inline int _find(int x) {
    if(father[x] != x)
        father[x] = _find(father[x]);
    return father[x];
}

inline void kruskal() {
    int ans = 0;
    vector <pair<int, int> > apm;
    sort(edges.begin(), edges.end());
    for(int i = 1 ; i <= n ; ++ i)
        father[i] = i;
    for(int i = 0 ; i < edges.size() ; ++ i) {
        int z = edges[i].first;
        int x = edges[i].second.first;
        int y = edges[i].second.second;
        int tx = _find(x);
        int ty = _find(y);
        if(tx == ty)
            continue;
        ans += z;
        apm.push_back(make_pair(x, y));
        father[tx] = ty;
    }
    fout << ans << ' ' << apm.size() << '\n';
    for(auto it : apm)
        fout << it.first << ' ' << it.second << '\n';
}

inline void prim() {
    memset(dist, oo, sizeof(dist));
    memset(father, 0, sizeof(father));
    dist[1] = 0;
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, 1));
    used[1] = 1;
    int totalcost = 0;
    vector <pair<int, int> > apm;
    while(!q.empty()) {
        int node = q.top().second;
        int cost = -q.top().first;
        q.pop();
        if(cost > dist[node])
            continue;
        if(!used[node]) {
            used[node] = 1;
            apm.push_back(make_pair(father[node], node));
            totalcost += cost;
        }
        for(auto it : g[node])
            if(!used[it.first] && dist[it.first] > it.second) {
                dist[it.first] = it.second;
                father[it.first] = node;
                q.push(make_pair(-dist[it.first], it.first));
            }
    }
    fout << '\n';
    fout << totalcost << ' ' << apm.size() << '\n';
    for(auto it : apm)
        fout << it.first << ' ' << it.second << '\n';
}

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        g[x].push_back(make_pair(y, z));
        g[y].push_back(make_pair(x, z));
        edges.push_back(make_pair(z, make_pair(x, y)));
    }
    kruskal();
    prim();
    cerr << getsize() << '\n';


}
