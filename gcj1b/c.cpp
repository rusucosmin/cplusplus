#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);

    int t, test = 0;
    cin >> t;
    while(t --) {
        int n;
        cin >> n;
        vector <pair<string, string> > v;
        for(int i = 0 ; i < n ; ++ i) {
            string a, b;
            cin >> a >> b;
            v.push_back({a,b});
        }
        int ans = 0;
        for(int i = 0 ; i < (1 << n) ; ++ i) {
            unordered_map<string, bool> a, b;
            int cnt = 0;
            for(int j = 0 ; j < n ; ++ j)
                if(!(j & (1 << i))) {
                    a[v[j].first] = 1;
                    b[v[j].second] = 1;
                }
                else
                    ++ cnt;
            bool ok = 1;
            for(int j = 0 ; j < n ; ++ j) {
                if(j & (1 << i))
                    if(!a[v[j].first] || !b[v[j].second])
                        ok = 0;
            }
            if(ok)
                ans = max(ans, cnt);
        }
        cout << "Case #" << ++ test << ": " << ans << '\n';
    }
}
