#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("ciclu.in");
ofstream fout("ciclu.out");

const int maxn = 1005;
const int oo = 2000000;

int n, m, dist[maxn], inqs[maxn];
vector <pair<int, int> > g[maxn], v[maxn];
queue <int> q;
bitset <maxn> inq;

inline bool check(int value) {
    for(int i = 0 ; i <= n ; ++ i) {
        dist[i] = oo;
        inqs[i] = 0;
        inq[i] = 0;
        v[i] = g[i];
        for(vector <pair<int, int> > :: iterator it = v[i].begin() ; it != v[i].end() ; ++ it)
            it->second -= value;
    }
    q.push(0);
    inq[0] = 1;
    inqs[0] = 1;
    dist[0] = 0;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        inq[node] = 0;
        for(vector <pair<int, int> > :: iterator it = v[node].begin() ; it != v[node].end() ; ++ it)
            if(dist[it->first] > dist[node] + it->second) {
                dist[it->first] = dist[node] + it->second;
                if(inq[it->first])
                    continue;
                inq[it->first] = 1;
                ++ inqs[it->first];
                if(inqs[it->first] > n)
                    return 1;
                q.push(it->first);
            }
    }
    return 0;
}

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        g[x].push_back(make_pair(y, z * 100));
    }
    for(int i = 1 ; i <= n ; ++ i)
        g[0].push_back(make_pair(i, 0));
    int li = -oo, ls = oo, mid, ans;
    while(li <= ls) {
        mid = ((li + ls) >> 1);
        if(check(mid)) {
            ans = mid;
            ls = mid - 1;
        }
        else
            li = mid + 1;
    }
    fout << mid * 0.01 - 0.01 << '\n';
}
