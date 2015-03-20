#include <iostream>
#include <vector>
#include <string.h>
#include <bitset>
#include <queue>
#include <fstream>

using namespace std;

ifstream fin("lanterna.in");
ofstream fout("lanterna.out");

const int maxn = 55;
const int maxk = 1005;
const int oo = 0x3f3f3f3f;


int n, k, m, dp[maxn][maxk];
bitset <maxn> ishome;

struct edge {
    int x, t, w;
    edge(int _x, int _t, int _w) {
        x = _x;
        t = _t;
        w = _w;
    }
};

vector <edge> g[maxn];
priority_queue<pair<int, pair<int, int> > > q;

inline int dijkstra(int k) {  /// dp[i][k] = costul minim de a ajunge in nodul i cu k wati ramasi
    memset(dp, oo, sizeof(dp));
    dp[1][k] = 0;
    q.push(make_pair(0, make_pair(1, k)));
    int ans = 0x3f3f3f3f;
    while(!q.empty()) {
        int node = q.top().second.first;
        int cost = -q.top().first;
        int wati = q.top().second.second;
        q.pop();
        if(cost > dp[node][wati])
            continue;
        if(node == n) {
            ans = min(ans, cost);
            continue;
        }
        for(vector <edge> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
            int newwats = wati - it->w;
            if(newwats < 0)
                continue;
            if(ishome[it->x])
                newwats = k;
            if(dp[it->x][newwats] > cost + it->t) {
                dp[it->x][newwats] = cost + it->t;
                q.push(make_pair(-dp[it->x][newwats], make_pair(it->x, newwats)));
            }
        }
    }
    return ans;
}

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void get(int &x) {
    x = 0;
    while(!isdigit(buff[pos]))
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    while(isdigit(buff[pos])) {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

bitset <maxk> inq[maxn];

inline int bellmanford(int k) {
    queue <pair<int, int> > q;
    memset(dp, oo, sizeof(dp));
    dp[1][k] = 0;
    q.push(make_pair(1, k));
    inq[1][k] = 1;
    int ans = 0x3f3f3f3f;
    while(!q.empty()) {
        int node = q.front().first;
        int wats = q.front().second;
        q.pop();
        inq[node][wats] = false;
        if(node == n)
            ans = min(ans, dp[node][wats]);
        for(vector <edge> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
            int newwats = wats - it->w;
            if(newwats < 0)
                continue;
            if(ishome[it->x])
                newwats = k;
            if(dp[it->x][newwats] > dp[node][wats] + it->t) {
                dp[it->x][newwats] = dp[node][wats] + it->t;
                if(inq[it->x][newwats])
                    continue;
                q.push(make_pair(it->x, newwats));
                inq[it->x][newwats] = 1;
            }
        }
    }
    return ans;
}

int main() {
    freopen("lanterna.in", "r", stdin);
    //fin >> n >> k;
    get(n); get(k);
    for(int i = 1 ; i <= n ; ++ i) {
        int x;
        get(x);
        ishome[i] = x;
    }
    //fin >> m;
    get(m);
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y, t, w;
        get(x); get(y); get(t); get(w);
        //fin >> x >> y >> t >> w;
        g[x].push_back(edge(y, t, w));
        g[y].push_back(edge(x, t, w));
    }
    int tmin = bellmanford(k);
    int st = 1, dr = k - 1, ans = k;
    while(st <= dr) {
        int mid = ((st + dr) >> 1);
        if(bellmanford(mid) == tmin) {
            ans = mid;
            dr = mid - 1;
        }
        else
            st = mid + 1;
    }
    fout << tmin << ' ' << ans << '\n';
}
