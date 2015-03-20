#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

const int maxn = 1000005;

int n, pi[maxn], cnt[maxn];
char s[maxn];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("126b.in", "r", stdin);
    freopen("126b.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> s + 1;
    n = strlen(s + 1);
    int k = 0;
    for(int i = 2 ; i <= n ; ++ i) {
        while(k > 0 && s[k + 1] != s[i])
            k = pi[k];
        if(s[k + 1] == s[i])
            ++ k;
        pi[i] = k;
        if(i != n)
            ++ cnt[pi[i]];
    }
    for(int i = n ; i > 0 ; -- i)
        cnt[pi[i]] += cnt[i];
    for(int length = pi[n] ; length ; length = pi[length]) {
        if(cnt[length]) {
            s[length + 1] = '\0';
            cout << s + 1 << '\n';
            return 0;
        }
    }
    cout << "Just a legend\n";
}
