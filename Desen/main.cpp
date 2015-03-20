#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("desen.in");
ofstream fout("desen.out");

const int maxn = 1005;

int n, father[maxn];
double dp[maxn][maxn];
vector <pair<int, int> > points;

inline double _dist(pair<int, int> a, pair<int, int> b) {
    return sqrt((double)(a.first - b.first) * (a.first - b.first) + (double)(a.second - b.second) * (a.second - b.second));
}

inline int _find(int x) {
    if(father[x] != x)
        father[x] = _find(father[x]);
    return father[x];
}

int main() {
    fin >> n;
    for(int i = 0 ; i < n ; ++ i) {
        int x, y;
        fin >> x >> y;
        points.push_back(make_pair(x, y));
    }
    fout << fixed << setprecision(6);
    for(int i = 0 ; i < n ; ++ i)
        for(int j = 0 ; j < n ; ++ j)
            dp[i][j] = dp[j][i] = _dist(points[i], points[j]);
    fout << 0.0 << '\n' << dp[0][1] << '\n';
    vector <pair<double, pair<int, int> > > apm;
    apm.push_back(make_pair(dp[0][1], make_pair(0, 1)));
    for(int i = 2 ; i < n ; ++ i) {
        for(int j = 0 ; j < i ; ++ j)
            apm.push_back(make_pair(dp[i][j], make_pair(i, j)));
        sort(apm.begin(), apm.end());
        vector <pair<double, pair<int, int> > > newapm;
        for(int node = 0 ; node <= i ; ++ node)
            father[node] = node;
        double ans = 0;
        for(int e = 0 ; e < apm.size() ; ++ e) {
            int tx = _find(apm[e].second.first);
            int ty = _find(apm[e].second.second);
            if(tx == ty)
                continue;
            ans += apm[e].first;
            father[tx] = ty;
            newapm.push_back(apm[e]);
        }
        apm = newapm;
        fout << ans << '\n';
    }
}
