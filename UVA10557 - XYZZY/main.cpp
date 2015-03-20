#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;

const int maxn = 105;
const int maxvalue = 105 * 105;
const int oo = 0x3f3f3f3f;

int dp[maxn][maxvalue];
int n, value[maxn];
bitset <maxvalue> used[maxn];
vector <int> g[maxn];

inline void djkstra() {
    queue <pair<int, int> > q;;
    q.push(make_pair(1, 100));
    used[1][100] = 1;
    while(!q.empty()) {
        int node = q.front().first;
        int cost = q.front().second;
        q.pop();
        if(node == n) {
            cout << "winnable\n";
            return ;
        }
        for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
            int newcost = cost + value[*it];
            if(newcost <= 0)
                continue;
            if(!used[*it][newcost]) {
                q.push(make_pair(*it, newcost));
                used[*it][newcost] = 1;
            }
        }
    }
    cout << "hopeless\n";
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    while(cin >> n) {
        if(n == -1)
            return 0;
        for(int i = 1 ; i <= n ; ++ i) {
            int cnt;
            cin >> value[i] >> cnt;
            for(int j = 1 ; j <= cnt ; ++ j) {
                int x;
                cin >> x;
                g[i].push_back(x);
            }
        }
        djkstra();
        for(int i = 1 ; i <= n ; ++ i) {
            vector <int> ().swap(g[i]);
            used[i].reset();
        }
    }

}
