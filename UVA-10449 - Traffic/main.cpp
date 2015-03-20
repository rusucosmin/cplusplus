#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const int maxn = 205;
const int oo = 0x3f3f3f3f;

queue <int> q;
vector <pair<int, int> > g[maxn];
bitset <maxn> inq;
int n, m, inqs[maxn], dist[maxn], a[maxn];

inline void bellmanford() {
    memset(dist, oo, sizeof(dist));
    memset(inqs, 0, sizeof(inqs));
    dist[1] = 0;
    q.push(1);
    inqs[1] = 0;
    while(!q.empty()) {
        int node = q.front();
        inq[node] = 0;
        q.pop();
        for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
            if(dist[it->first] > dist[node] + it->second) {
                dist[it->first] = dist[node] + it->second;
                if(inq[it->first])
                    continue;
                if(++ inqs[it->first] > n)
                    continue;
                inq[it->first] = 1;
                q.push(it->first);
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    int test = 0;
    while(cin >> n) {
        for(int i = 1 ; i <= n ; ++ i)
            cin >> a[i];
        cin >> m;
        for(int i = 1 ; i <= m ; ++ i) {
            int x, y;
            cin >> x >> y;
            g[x].push_back(make_pair(y, (a[y] - a[x]) * (a[y] - a[x]) * (a[y] - a[x])));
        }
        bellmanford();
        int q;
        cin >> q;
        cout << "Set #" << ++ test << '\n';
        while(q--) {
            int x;
            cin >> x;
            if(dist[x] == oo || dist[x] < 3)
                cout << "?\n";
            else
                cout << dist[x] << '\n';
        }
        for(int i = 1 ; i <= n ; ++ i)
            vector <pair<int, int> > ().swap(g[i]);
    }
}
