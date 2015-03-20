/// http://www.spoj.com/problems/BLINNET/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 10005;

int father[maxn];

inline int _find(int x) {
    if(father[x] != x)
        father[x] = _find(father[x]);
    return father[x];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("blinnet.in", "r", stdin);
    freopen("blinnet.out", "w", stdout);
    #endif // ONLINE_JUDGE
    int t, n;
    cin >> t;
    while(t -- ) {
        cin >> n;
        vector <pair<int, pair<int, int> > > edges;
        for(int i = 1 ; i <= n ; ++ i) {
            string a; cin >> a;
            father[i] = i;
            int x; cin >> x;
            for(int j = 1 ; j <= x ; ++ j) {
                int y, z;
                cin >> y >> z;
                edges.push_back(make_pair(z, make_pair(i, y)));
            }
        }
        sort(edges.begin(), edges.end());
        long long ans = 0;
        for(int i = 0 ; i < edges.size() ; ++ i) {
            int tx = _find(edges[i].second.first);
            int ty = _find(edges[i].second.second);
            if(tx == ty)
                continue;
            father[tx] = ty;
            ans += edges[i].first;
        }
        cout << ans << '\n';
    }
}
