#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 100005;

int t, pi[maxn];
char s[maxn];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    while(cin.getline(s + 1, maxn)) {
        if(s[1] == '*')
            break;
        int k = 0;
        int n = strlen(s + 1);
        for(int i = 2 ; i <= n ; ++ i) {
            while(k > 0 && s[k + 1] != s[i])
                k = pi[k];
            if(s[k + 1] == s[i])
                ++ k;
            pi[i] = k;
        }
        if(n % (n - pi[n]) == 0)
            cout << n / (n - pi[n]) << '\n';
        else
            cout << "1\n";
    }
}
