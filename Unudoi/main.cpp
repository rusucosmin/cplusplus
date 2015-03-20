#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const int maxn = 50005;

int n, m;
vector <int> a, b;
bitset <maxn> used;

int main() {
    freopen("unudoi.in", "r", stdin);
    freopen("unudoi.out", "w", stdout);
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < n ; ++ i) {
        int x;
        scanf("%d", &x);
        a.push_back(x);
    }
    for(int i = 0 ; i < m ; ++ i) {
        int x;
        scanf("%d", &x);
        b.push_back(x);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int ans = 0;
    for(int i = 0 ; i < a.size() ; ++ i) {
        int pos = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        if(!used[pos])
            ++ ans;
        used[pos] = 1;
    }
    printf("%d\n", ans);
}
