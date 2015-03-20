#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 100005;

char s[maxn], w[maxn], rs[maxn];
int n, m, cnt, pi[maxn], suff[maxn], pref[maxn];

inline void build(char *w, char *s, int *suff) {
    int k = 0;
    for(int i = 2 ; i <= m ; ++ i) {
        while(k > 0 && w[k + 1] != w[i])
            k = pi[k];
        if(w[k + 1] == w[i])
            ++ k;
        pi[i] = k;
    }
    k = 0;
    suff[0] = suff[n + 1] = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        while(k > 0 && w[k + 1] != s[i])
            k = pi[k];
        if(w[k + 1] == s[i])
            ++ k;
        suff[i] = max(suff[i - 1], k);
        if(k == m)
            k = pi[k];
    }
}

inline bool doit() {
    if(m == 1)
        return 0;
    build(w, s, suff);
    for(int i = 1 ; i <= m / 2 ; ++ i)
        swap(w[i], w[m - i + 1]);
    build(w, rs, pref);
    for(int i = 1 ; i < n ; ++ i)
        if(suff[i] + pref[n - i] >= m && suff[i] > 0 && pref[n - i] > 0)
            return 1;
    return 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> s + 1 >> cnt;
    n = strlen(s + 1);
    strcpy(rs + 1, s + 1);
    for(int i = 1 ; i <= n / 2 ; ++ i)
        swap(rs[i], rs[n - i + 1]);
    int ans = 0;
    for(int i = 1 ; i <= cnt ; ++ i) {
        cin >> w + 1;
        m = strlen(w + 1);
        ans += doit();
    }
    cout << ans << '\n';
}
