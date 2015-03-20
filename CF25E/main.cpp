#include <iostream>
#include <fstream>
#include <bitset>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100505;
const int oo = 0x3f3f3f3f;

char s[5][maxn];
int n[5], pi[5][maxn], st[5], dp[5][5];
int ans;
bitset <10> used, removed;

inline int get(int ind1, int ind2) {
    int k = 0;
    for(int i = 1 ; i <= n[ind2] ; ++ i) {
        while(k > 0 && s[ind1][k + 1] != s[ind2][i])
            k = pi[ind1][k];
        if(s[ind1][k + 1] == s[ind2][i])
            ++ k;
        if(k == n[ind1])
            return -1;
    }
    return k;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    while(cin >> s[0] + 1 >> s[1] + 1 >> s[2] + 1) {
        int ans = 0;
        for(int ind = 0 ; ind < 3 ; ++ ind) {
            n[ind] = strlen(s[ind] + 1);
            ans = ans + n[ind];
            int k = 0;
            for(int i = 2 ; i <= n[ind] ; ++ i) {
                while(k > 0 && s[ind][k + 1] != s[ind][i])
                    k = pi[ind][k];
                if(s[ind][k + 1] == s[ind][i])
                    ++ k;
                pi[ind][i] = k;
            }
        }
        removed.reset();

        for(int i = 0 ; i < 3 ; ++ i)
            for(int j = 0 ; j < 3 ; ++ j) {
                if(i == j)
                    continue;
                dp[i][j] = get(i, j);
                if(dp[i][j] == -1)
                    removed[i] = 1;
            }
        vector <int> v;
        for(int i = 0 ; i < 3 ; ++ i)
            if(!removed[i])
                v.push_back(i);
        if(v.size())
        do {
            int actans = n[v[0]];
            for(int i = 1 ; i < v.size() ; ++ i)
                actans = actans + n[v[i]] - dp[v[i]][v[i - 1]];
            ans = min(ans, actans);
        }while(next_permutation(v.begin(), v.end()));
        else
            ans = max(n[0], max(n[1], n[2]));
        cout << ans << '\n';
    }

}
