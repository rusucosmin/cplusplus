#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, k;

struct classcomp {
    inline bool operator () (const pair<int, int> &a, const pair<int, int> & b) const {
        return a.second < b.second;
    }
};

inline long long solve(vector <pair<int, int> > v) {
    sort(v.begin(), v.end(), classcomp());
    int xmin = v[0].first;
    long long ans = 0;
    for(int i = 0 ; i < v.size() ; ++ i) {
        int x = v[i].first;
        int y = v[i].second;
        ans = max(ans, 1LL * xmin * y);
        xmin = min(xmin, x);
    }
    ans = max(ans, 1LL * n * v[0].second);
    ans = max(ans, 1ll * xmin * m);
    return ans;
}

int main() {
    vector <pair<int, int> > v;
    freopen("piscina.in", "r", stdin);
    ofstream fout("piscina.out");
    scanf("%d %d", &n, &m);
    scanf("%d", &k);
    for(int i = 0 ; i < k ; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        v.push_back(make_pair(x, y));
    }
    long long ans = solve(v);
    for(int i = 0 ; i < k ; ++ i)
        v[i].first = n - v[i].first;
    ans = max(ans, solve(v));
    for(int i = 0 ; i < k ; ++ i) {
        v[i].first = n - v[i].first;
        v[i].second = m - v[i].second;
    }
    ans = max(ans, solve(v));
    for(int i = 0 ; i < k ; ++ i)
        v[i].first = n - v[i].first;
    ans = max(ans, solve(v));
    fout << ans << '\n';
}
