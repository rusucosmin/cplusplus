#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int maxn = 1000005;

int n, pi[maxn];
char s[maxn];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    while(cin >> n >> s + 1) {
        if(n == -1)
            return 0;
        if(s[1] == '*')
            return 0;
        int m = strlen(s + 1);
        int k = 0;
        for(int i = 2 ; i <= m ; ++ i) {
            while(k > 0 && s[k + 1] != s[i])
                k = pi[k];
            if(s[k + 1] == s[i])
                ++ k;
            pi[i] = k;
        }
        cout << max(0, (n - pi[m]) / (m - pi[m])) << '\n';
    }

}
